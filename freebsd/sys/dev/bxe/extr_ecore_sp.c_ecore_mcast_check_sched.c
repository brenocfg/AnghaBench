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
struct TYPE_2__ {int /*<<< orphan*/  pstate; } ;
struct ecore_mcast_obj {TYPE_1__ raw; int /*<<< orphan*/  sched_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_mcast_check_sched(struct ecore_mcast_obj *o)
{
	return !!ECORE_TEST_BIT(o->sched_state, o->raw.pstate);
}