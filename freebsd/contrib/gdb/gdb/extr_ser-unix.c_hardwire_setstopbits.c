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
struct TYPE_4__ {int /*<<< orphan*/  c_cflag; } ;
struct TYPE_3__ {int /*<<< orphan*/  c_cflag; } ;
struct hardwire_ttystate {TYPE_2__ termio; TYPE_1__ termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSTOPB ; 
#define  SERIAL_1_AND_A_HALF_STOPBITS 130 
#define  SERIAL_1_STOPBITS 129 
#define  SERIAL_2_STOPBITS 128 
 scalar_t__ get_tty_state (struct serial*,struct hardwire_ttystate*) ; 
 int set_tty_state (struct serial*,struct hardwire_ttystate*) ; 

__attribute__((used)) static int
hardwire_setstopbits (struct serial *scb, int num)
{
  struct hardwire_ttystate state;
  int newbit;

  if (get_tty_state (scb, &state))
    return -1;

  switch (num)
    {
    case SERIAL_1_STOPBITS:
      newbit = 0;
      break;
    case SERIAL_1_AND_A_HALF_STOPBITS:
    case SERIAL_2_STOPBITS:
      newbit = 1;
      break;
    default:
      return 1;
    }

#ifdef HAVE_TERMIOS
  if (!newbit)
    state.termios.c_cflag &= ~CSTOPB;
  else
    state.termios.c_cflag |= CSTOPB;	/* two bits */
#endif

#ifdef HAVE_TERMIO
  if (!newbit)
    state.termio.c_cflag &= ~CSTOPB;
  else
    state.termio.c_cflag |= CSTOPB;	/* two bits */
#endif

#ifdef HAVE_SGTTY
  return 0;			/* sgtty doesn't support this */
#endif

  return set_tty_state (scb, &state);
}