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
struct serial {int dummy; } ;
struct TYPE_4__ {int sg_ispeed; int sg_ospeed; } ;
struct TYPE_3__ {int c_cflag; } ;
struct hardwire_ttystate {TYPE_2__ sgttyb; TYPE_1__ termio; int /*<<< orphan*/  termios; } ;

/* Variables and functions */
 int CBAUD ; 
 int CIBAUD ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  cfsetispeed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfsetospeed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ get_tty_state (struct serial*,struct hardwire_ttystate*) ; 
 int rate_to_code (int) ; 
 int set_tty_state (struct serial*,struct hardwire_ttystate*) ; 

__attribute__((used)) static int
hardwire_setbaudrate (struct serial *scb, int rate)
{
  struct hardwire_ttystate state;
  int baud_code = rate_to_code (rate);
  
  if (baud_code < 0)
    {
      /* The baud rate was not valid.
         A warning has already been issued. */
      errno = EINVAL;
      return -1;
    }

  if (get_tty_state (scb, &state))
    return -1;

#ifdef HAVE_TERMIOS
  cfsetospeed (&state.termios, baud_code);
  cfsetispeed (&state.termios, baud_code);
#endif

#ifdef HAVE_TERMIO
#ifndef CIBAUD
#define CIBAUD CBAUD
#endif

  state.termio.c_cflag &= ~(CBAUD | CIBAUD);
  state.termio.c_cflag |= baud_code;
#endif

#ifdef HAVE_SGTTY
  state.sgttyb.sg_ispeed = baud_code;
  state.sgttyb.sg_ospeed = baud_code;
#endif

  return set_tty_state (scb, &state);
}