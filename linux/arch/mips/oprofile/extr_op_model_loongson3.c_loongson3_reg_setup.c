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
struct op_counter_config {scalar_t__ enabled; scalar_t__ count; scalar_t__ user; scalar_t__ kernel; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {unsigned int control1; unsigned int control2; scalar_t__ ctr2_enable; scalar_t__ ctr1_enable; scalar_t__ reset_counter2; scalar_t__ reset_counter1; } ;

/* Variables and functions */
 unsigned int LOONGSON3_PERFCTRL_ENABLE ; 
 unsigned int LOONGSON3_PERFCTRL_EVENT (int,int /*<<< orphan*/ ) ; 
 unsigned int LOONGSON3_PERFCTRL_EXL ; 
 unsigned int LOONGSON3_PERFCTRL_KERNEL ; 
 unsigned int LOONGSON3_PERFCTRL_USER ; 
 TYPE_1__ reg ; 

__attribute__((used)) static void loongson3_reg_setup(struct op_counter_config *ctr)
{
	unsigned int control1 = 0;
	unsigned int control2 = 0;

	reg.reset_counter1 = 0;
	reg.reset_counter2 = 0;
	/* Compute the performance counter control word. */
	/* For now count kernel and user mode */
	if (ctr[0].enabled) {
		control1 |= LOONGSON3_PERFCTRL_EVENT(0, ctr[0].event) |
					LOONGSON3_PERFCTRL_ENABLE;
		if (ctr[0].kernel)
			control1 |= LOONGSON3_PERFCTRL_KERNEL;
		if (ctr[0].user)
			control1 |= LOONGSON3_PERFCTRL_USER;
		reg.reset_counter1 = 0x8000000000000000ULL - ctr[0].count;
	}

	if (ctr[1].enabled) {
		control2 |= LOONGSON3_PERFCTRL_EVENT(1, ctr[1].event) |
					LOONGSON3_PERFCTRL_ENABLE;
		if (ctr[1].kernel)
			control2 |= LOONGSON3_PERFCTRL_KERNEL;
		if (ctr[1].user)
			control2 |= LOONGSON3_PERFCTRL_USER;
		reg.reset_counter2 = 0x8000000000000000ULL - ctr[1].count;
	}

	if (ctr[0].enabled)
		control1 |= LOONGSON3_PERFCTRL_EXL;
	if (ctr[1].enabled)
		control2 |= LOONGSON3_PERFCTRL_EXL;

	reg.control1 = control1;
	reg.control2 = control2;
	reg.ctr1_enable = ctr[0].enabled;
	reg.ctr2_enable = ctr[1].enabled;
}