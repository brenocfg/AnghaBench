#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  epref; } ;
struct TYPE_6__ {TYPE_1__ status_enq; } ;
struct uni_all {TYPE_2__ u; } ;
struct call {scalar_t__ cnt322; TYPE_3__* uni; scalar_t__ se_active; int /*<<< orphan*/  stat_epref; scalar_t__ mine; int /*<<< orphan*/  cref; } ;
struct TYPE_7__ {scalar_t__ init322; int /*<<< orphan*/  cause; int /*<<< orphan*/  timer322; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CAUSE_TIMER (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_MSG_ORIG (struct uni_all*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIMER_START_CALL (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uni_all* UNI_ALLOC () ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_RECOVER ; 
 int /*<<< orphan*/  UNI_FAC_TIMEOUT ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  UNI_STATUS_ENQ ; 
 int /*<<< orphan*/  VERBOSE (TYPE_3__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  t322 ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,TYPE_3__*) ; 

__attribute__((used)) static void
unx_t322(struct call *c)
{
	struct uni_all *stat;

	VERBOSE(c->uni, UNI_FAC_TIMEOUT, 1, "call %u/%s T322 tick %d",
	    c->cref, c->mine ? "mine" : "his", c->cnt322 + 1);

	if (++c->cnt322 < c->uni->init322) {
		if ((stat = UNI_ALLOC()) != NULL) {
			MK_MSG_ORIG(stat, UNI_STATUS_ENQ, c->cref, !c->mine);
			stat->u.status_enq.epref = c->stat_epref;
			(void)uni_send_output(stat, c->uni);
			UNI_FREE(stat);
		}
		TIMER_START_CALL(c, t322, c->uni->timer322);
		return;
	}
	c->se_active = 0;

	MK_IE_CAUSE(c->uni->cause, UNI_CAUSE_LOC_USER, UNI_CAUSE_RECOVER);
	ADD_CAUSE_TIMER(c->uni->cause, "322");

	clear_callD(c);
}