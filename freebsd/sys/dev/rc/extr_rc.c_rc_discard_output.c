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
struct rc_chans {int rc_flags; TYPE_2__* rc_tp; int /*<<< orphan*/  rc_obufend; int /*<<< orphan*/  rc_optr; TYPE_1__* rc_rcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  t_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  sc_scheduled_event; } ;

/* Variables and functions */
 scalar_t__ LOTS_OF_EVENTS ; 
 int RC_DOXXFER ; 
 int /*<<< orphan*/  TS_BUSY ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  ttwwakeup (TYPE_2__*) ; 

__attribute__((used)) static void
rc_discard_output(struct rc_chans *rc)
{
	critical_enter();
	if (rc->rc_flags & RC_DOXXFER) {
		rc->rc_rcb->sc_scheduled_event -= LOTS_OF_EVENTS;
		rc->rc_flags &= ~RC_DOXXFER;
	}
	rc->rc_optr = rc->rc_obufend;
	rc->rc_tp->t_state &= ~TS_BUSY;
	critical_exit();
	ttwwakeup(rc->rc_tp);
}