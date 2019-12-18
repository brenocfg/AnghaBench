#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serial {int dummy; } ;
struct TYPE_2__ {int sg_flags; } ;
struct hardwire_ttystate {TYPE_1__ sgttyb; } ;
typedef  scalar_t__ serial_ttystate ;

/* Variables and functions */
 int CBREAK ; 
 int RAW ; 
 int set_tty_state (struct serial*,struct hardwire_ttystate*) ; 

__attribute__((used)) static int
hardwire_noflush_set_tty_state (struct serial *scb,
				serial_ttystate new_ttystate,
				serial_ttystate old_ttystate)
{
  struct hardwire_ttystate new_state;
#ifdef HAVE_SGTTY
  struct hardwire_ttystate *state = (struct hardwire_ttystate *) old_ttystate;
#endif

  new_state = *(struct hardwire_ttystate *) new_ttystate;

  /* Don't change in or out of raw mode; we don't want to flush input.
     termio and termios have no such restriction; for them flushing input
     is separate from setting the attributes.  */

#ifdef HAVE_SGTTY
  if (state->sgttyb.sg_flags & RAW)
    new_state.sgttyb.sg_flags |= RAW;
  else
    new_state.sgttyb.sg_flags &= ~RAW;

  /* I'm not sure whether this is necessary; the manpage just mentions
     RAW not CBREAK.  */
  if (state->sgttyb.sg_flags & CBREAK)
    new_state.sgttyb.sg_flags |= CBREAK;
  else
    new_state.sgttyb.sg_flags &= ~CBREAK;
#endif

  return set_tty_state (scb, &new_state);
}