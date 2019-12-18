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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fman_bmi_regs {int /*<<< orphan*/ * fmbm_pp; } ;

/* Variables and functions */
 int BMI_EXTRA_NUM_OF_TASKS_SHIFT ; 
 int BMI_NUM_OF_EXTRA_TASKS_MASK ; 
 int BMI_NUM_OF_TASKS_MASK ; 
 int BMI_NUM_OF_TASKS_SHIFT ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_num_of_tasks(struct fman_bmi_regs *bmi_rg,
				uint8_t port_id,
				uint8_t num_tasks,
				uint8_t num_extra_tasks)
{
	uint32_t tmp;

	if ((port_id > 63) || (port_id < 1))
	    return;

	/* calculate reg */
	tmp = ioread32be(&bmi_rg->fmbm_pp[port_id - 1]) &
			~(BMI_NUM_OF_TASKS_MASK | BMI_NUM_OF_EXTRA_TASKS_MASK);
	tmp |= (uint32_t)(((num_tasks - 1) << BMI_NUM_OF_TASKS_SHIFT) |
			(num_extra_tasks << BMI_EXTRA_NUM_OF_TASKS_SHIFT));
	iowrite32be(tmp, &bmi_rg->fmbm_pp[port_id - 1]);
}