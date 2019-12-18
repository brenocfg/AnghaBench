#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct serial {int current_timeout; int timeout_remaining; scalar_t__ fd; } ;
struct TYPE_4__ {int* c_cc; } ;
struct TYPE_3__ {int* c_cc; } ;
struct hardwire_ttystate {TYPE_2__ termio; TYPE_1__ termios; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int SERIAL_ERROR ; 
 int SERIAL_TIMEOUT ; 
 size_t VMIN ; 
 size_t VTIME ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ get_tty_state (struct serial*,struct hardwire_ttystate*) ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ set_tty_state (struct serial*,struct hardwire_ttystate*) ; 

__attribute__((used)) static int
wait_for (struct serial *scb, int timeout)
{
#ifdef HAVE_SGTTY
  while (1)
    {
      struct timeval tv;
      fd_set readfds;
      int numfds;

      /* NOTE: Some OS's can scramble the READFDS when the select()
         call fails (ex the kernel with Red Hat 5.2).  Initialize all
         arguments before each call. */

      tv.tv_sec = timeout;
      tv.tv_usec = 0;

      FD_ZERO (&readfds);
      FD_SET (scb->fd, &readfds);

      if (timeout >= 0)
	numfds = select (scb->fd + 1, &readfds, 0, 0, &tv);
      else
	numfds = select (scb->fd + 1, &readfds, 0, 0, 0);

      if (numfds <= 0)
	if (numfds == 0)
	  return SERIAL_TIMEOUT;
	else if (errno == EINTR)
	  continue;
	else
	  return SERIAL_ERROR;	/* Got an error from select or poll */

      return 0;
    }
#endif /* HAVE_SGTTY */

#if defined HAVE_TERMIO || defined HAVE_TERMIOS
  if (timeout == scb->current_timeout)
    return 0;

  scb->current_timeout = timeout;

  {
    struct hardwire_ttystate state;

    if (get_tty_state (scb, &state))
      fprintf_unfiltered (gdb_stderr, "get_tty_state failed: %s\n", safe_strerror (errno));

#ifdef HAVE_TERMIOS
    if (timeout < 0)
      {
	/* No timeout.  */
	state.termios.c_cc[VTIME] = 0;
	state.termios.c_cc[VMIN] = 1;
      }
    else
      {
	state.termios.c_cc[VMIN] = 0;
	state.termios.c_cc[VTIME] = timeout * 10;
	if (state.termios.c_cc[VTIME] != timeout * 10)
	  {

	    /* If c_cc is an 8-bit signed character, we can't go 
	       bigger than this.  If it is always unsigned, we could use
	       25.  */

	    scb->current_timeout = 12;
	    state.termios.c_cc[VTIME] = scb->current_timeout * 10;
	    scb->timeout_remaining = timeout - scb->current_timeout;
	  }
      }
#endif

#ifdef HAVE_TERMIO
    if (timeout < 0)
      {
	/* No timeout.  */
	state.termio.c_cc[VTIME] = 0;
	state.termio.c_cc[VMIN] = 1;
      }
    else
      {
	state.termio.c_cc[VMIN] = 0;
	state.termio.c_cc[VTIME] = timeout * 10;
	if (state.termio.c_cc[VTIME] != timeout * 10)
	  {
	    /* If c_cc is an 8-bit signed character, we can't go 
	       bigger than this.  If it is always unsigned, we could use
	       25.  */

	    scb->current_timeout = 12;
	    state.termio.c_cc[VTIME] = scb->current_timeout * 10;
	    scb->timeout_remaining = timeout - scb->current_timeout;
	  }
      }
#endif

    if (set_tty_state (scb, &state))
      fprintf_unfiltered (gdb_stderr, "set_tty_state failed: %s\n", safe_strerror (errno));

    return 0;
  }
#endif /* HAVE_TERMIO || HAVE_TERMIOS */
}