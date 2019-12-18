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
 int /*<<< orphan*/  ECORE_CLEAR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_SMP_MB_AFTER_CLEAR_BIT () ; 
 int /*<<< orphan*/  ECORE_SMP_MB_BEFORE_CLEAR_BIT () ; 

__attribute__((used)) static void ecore_mcast_clear_sched(struct ecore_mcast_obj *o)
{
	ECORE_SMP_MB_BEFORE_CLEAR_BIT();
	ECORE_CLEAR_BIT(o->sched_state, o->raw.pstate);
	ECORE_SMP_MB_AFTER_CLEAR_BIT();
}