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
struct op_counter_config {scalar_t__ enabled; scalar_t__ user; scalar_t__ kernel; scalar_t__ count; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {unsigned int ctrl; scalar_t__ cnt2_enabled; scalar_t__ cnt1_enabled; scalar_t__ reset_counter2; scalar_t__ reset_counter1; } ;

/* Variables and functions */
 unsigned int LOONGSON2_PERFCTRL_ENABLE ; 
 unsigned int LOONGSON2_PERFCTRL_EVENT (int,int /*<<< orphan*/ ) ; 
 unsigned int LOONGSON2_PERFCTRL_EXL ; 
 unsigned int LOONGSON2_PERFCTRL_KERNEL ; 
 unsigned int LOONGSON2_PERFCTRL_USER ; 
 TYPE_1__ reg ; 

__attribute__((used)) static void loongson2_reg_setup(struct op_counter_config *cfg)
{
	unsigned int ctrl = 0;

	reg.reset_counter1 = 0;
	reg.reset_counter2 = 0;

	/*
	 * Compute the performance counter ctrl word.
	 * For now, count kernel and user mode.
	 */
	if (cfg[0].enabled) {
		ctrl |= LOONGSON2_PERFCTRL_EVENT(0, cfg[0].event);
		reg.reset_counter1 = 0x80000000ULL - cfg[0].count;
	}

	if (cfg[1].enabled) {
		ctrl |= LOONGSON2_PERFCTRL_EVENT(1, cfg[1].event);
		reg.reset_counter2 = 0x80000000ULL - cfg[1].count;
	}

	if (cfg[0].enabled || cfg[1].enabled) {
		ctrl |= LOONGSON2_PERFCTRL_EXL | LOONGSON2_PERFCTRL_ENABLE;
		if (cfg[0].kernel || cfg[1].kernel)
			ctrl |= LOONGSON2_PERFCTRL_KERNEL;
		if (cfg[0].user || cfg[1].user)
			ctrl |= LOONGSON2_PERFCTRL_USER;
	}

	reg.ctrl = ctrl;

	reg.cnt1_enabled = cfg[0].enabled;
	reg.cnt2_enabled = cfg[1].enabled;
}