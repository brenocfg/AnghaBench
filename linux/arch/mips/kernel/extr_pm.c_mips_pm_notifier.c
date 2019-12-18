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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CPU_PM_ENTER 130 
#define  CPU_PM_ENTER_FAILED 129 
#define  CPU_PM_EXIT 128 
 int NOTIFY_OK ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  mips_cpu_restore () ; 
 int mips_cpu_save () ; 

__attribute__((used)) static int mips_pm_notifier(struct notifier_block *self, unsigned long cmd,
			    void *v)
{
	int ret;

	switch (cmd) {
	case CPU_PM_ENTER:
		ret = mips_cpu_save();
		if (ret)
			return NOTIFY_STOP;
		break;
	case CPU_PM_ENTER_FAILED:
	case CPU_PM_EXIT:
		mips_cpu_restore();
		break;
	}

	return NOTIFY_OK;
}