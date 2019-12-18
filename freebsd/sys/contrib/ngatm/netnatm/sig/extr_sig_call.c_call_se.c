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
struct uni_all {int dummy; } ;
struct call {int se_active; TYPE_1__* uni; int /*<<< orphan*/  mine; int /*<<< orphan*/  cref; int /*<<< orphan*/  stat_epref; scalar_t__ cnt322; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer322; } ;

/* Variables and functions */
 int /*<<< orphan*/  MK_MSG_ORIG (struct uni_all*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIMER_START_CALL (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uni_all* UNI_ALLOC () ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  UNI_STATUS_ENQ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t322 ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,TYPE_1__*) ; 

__attribute__((used)) static void
call_se(struct call *c)
{
	struct uni_all *stat;

	c->cnt322 = 0;
	if (c->se_active)
		return;

	memset(&c->stat_epref, 0, sizeof(c->stat_epref));
	if ((stat = UNI_ALLOC()) != NULL) {
		MK_MSG_ORIG(stat, UNI_STATUS_ENQ, c->cref, !c->mine);
		(void)uni_send_output(stat, c->uni);
		UNI_FREE(stat);
	}

	TIMER_START_CALL(c, t322, c->uni->timer322);
	c->se_active = 1;
}