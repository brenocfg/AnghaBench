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

/* Variables and functions */
 scalar_t__ HALFLIFE ; 
 int /*<<< orphan*/  calc_converged_max () ; 
 int /*<<< orphan*/  calc_runnable_avg_yN_inv () ; 
 int /*<<< orphan*/  pow (double,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  y ; 

void main(void)
{
	printf("/* Generated by Documentation/scheduler/sched-pelt; do not modify. */\n\n");

	y = pow(0.5, 1/(double)HALFLIFE);

	calc_runnable_avg_yN_inv();
//	calc_runnable_avg_yN_sum();
	calc_converged_max();
//	calc_accumulated_sum_32();
}