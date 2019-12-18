#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct serial {int /*<<< orphan*/  fd; } ;
struct hardwire_ttystate {int /*<<< orphan*/  sgttyb; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCSBRK ; 
 int /*<<< orphan*/  TIOCSETP ; 
 scalar_t__ get_tty_state (struct serial*,struct hardwire_ttystate*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tcdrain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hardwire_drain_output (struct serial *scb)
{
#ifdef HAVE_TERMIOS
  return tcdrain (scb->fd);
#endif

#ifdef HAVE_TERMIO
  return ioctl (scb->fd, TCSBRK, 1);
#endif

#ifdef HAVE_SGTTY
  /* Get the current state and then restore it using TIOCSETP,
     which should cause the output to drain and pending input
     to be discarded. */
  {
    struct hardwire_ttystate state;
    if (get_tty_state (scb, &state))
      {
	return (-1);
      }
    else
      {
	return (ioctl (scb->fd, TIOCSETP, &state.sgttyb));
      }
  }
#endif
}