#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum cps_pm_state { ____Placeholder_cps_pm_state } cps_pm_state ;

/* Variables and functions */
 int /*<<< orphan*/  state_support ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

bool cps_pm_support_state(enum cps_pm_state state)
{
	return test_bit(state, state_support);
}