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
 scalar_t__ create_power_saving_task () ; 
 int /*<<< orphan*/  destroy_power_saving_task () ; 
 unsigned int ps_tsk_num ; 

__attribute__((used)) static void set_power_saving_task_num(unsigned int num)
{
	if (num > ps_tsk_num) {
		while (ps_tsk_num < num) {
			if (create_power_saving_task())
				return;
		}
	} else if (num < ps_tsk_num) {
		while (ps_tsk_num > num)
			destroy_power_saving_task();
	}
}