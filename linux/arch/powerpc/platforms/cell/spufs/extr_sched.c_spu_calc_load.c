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
 int /*<<< orphan*/  EXP_1 ; 
 int /*<<< orphan*/  EXP_15 ; 
 int /*<<< orphan*/  EXP_5 ; 
 unsigned long FIXED_1 ; 
 int /*<<< orphan*/  calc_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long count_active_contexts () ; 
 int /*<<< orphan*/ * spu_avenrun ; 

__attribute__((used)) static void spu_calc_load(void)
{
	unsigned long active_tasks; /* fixed-point */

	active_tasks = count_active_contexts() * FIXED_1;
	spu_avenrun[0] = calc_load(spu_avenrun[0], EXP_1, active_tasks);
	spu_avenrun[1] = calc_load(spu_avenrun[1], EXP_5, active_tasks);
	spu_avenrun[2] = calc_load(spu_avenrun[2], EXP_15, active_tasks);
}