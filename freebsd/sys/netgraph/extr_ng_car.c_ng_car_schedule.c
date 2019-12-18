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
struct TYPE_2__ {int cir; } ;
struct hookinfo {int tc; int /*<<< orphan*/  hook; int /*<<< orphan*/  q_callout; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_car_q_event ; 

__attribute__((used)) static void
ng_car_schedule(struct hookinfo *hinfo)
{
	int 	delay;

	delay = (-(hinfo->tc)) * hz * 8 / hinfo->conf.cir + 1;

	ng_callout(&hinfo->q_callout, NG_HOOK_NODE(hinfo->hook), hinfo->hook,
	    delay, &ng_car_q_event, NULL, 0);
}