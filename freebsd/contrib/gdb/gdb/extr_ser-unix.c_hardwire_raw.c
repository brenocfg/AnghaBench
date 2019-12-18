#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct serial {scalar_t__ current_timeout; } ;
struct TYPE_6__ {int sg_flags; } ;
struct TYPE_5__ {int c_cflag; scalar_t__* c_cc; scalar_t__ c_lflag; scalar_t__ c_oflag; scalar_t__ c_iflag; } ;
struct TYPE_4__ {int c_cflag; scalar_t__* c_cc; scalar_t__ c_lflag; scalar_t__ c_oflag; scalar_t__ c_iflag; } ;
struct hardwire_ttystate {TYPE_3__ sgttyb; TYPE_2__ termio; TYPE_1__ termios; } ;

/* Variables and functions */
 int ANYP ; 
 int CBREAK ; 
 int CLOCAL ; 
 int CS8 ; 
 int CSIZE ; 
 int ECHO ; 
 int PARENB ; 
 int RAW ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ get_tty_state (struct serial*,struct hardwire_ttystate*) ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ set_tty_state (struct serial*,struct hardwire_ttystate*) ; 

__attribute__((used)) static void
hardwire_raw (struct serial *scb)
{
  struct hardwire_ttystate state;

  if (get_tty_state (scb, &state))
    fprintf_unfiltered (gdb_stderr, "get_tty_state failed: %s\n", safe_strerror (errno));

#ifdef HAVE_TERMIOS
  state.termios.c_iflag = 0;
  state.termios.c_oflag = 0;
  state.termios.c_lflag = 0;
  state.termios.c_cflag &= ~(CSIZE | PARENB);
  state.termios.c_cflag |= CLOCAL | CS8;
  state.termios.c_cc[VMIN] = 0;
  state.termios.c_cc[VTIME] = 0;
#endif

#ifdef HAVE_TERMIO
  state.termio.c_iflag = 0;
  state.termio.c_oflag = 0;
  state.termio.c_lflag = 0;
  state.termio.c_cflag &= ~(CSIZE | PARENB);
  state.termio.c_cflag |= CLOCAL | CS8;
  state.termio.c_cc[VMIN] = 0;
  state.termio.c_cc[VTIME] = 0;
#endif

#ifdef HAVE_SGTTY
  state.sgttyb.sg_flags |= RAW | ANYP;
  state.sgttyb.sg_flags &= ~(CBREAK | ECHO);
#endif

  scb->current_timeout = 0;

  if (set_tty_state (scb, &state))
    fprintf_unfiltered (gdb_stderr, "set_tty_state failed: %s\n", safe_strerror (errno));
}