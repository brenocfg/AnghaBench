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
struct module {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  POWER_PM_TYPE_APM ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  power_pm_get_type () ; 

__attribute__((used)) static int
apm_modevent(struct module *mod, int event, void *junk)
{

	switch (event) {
	case MOD_LOAD:
		if (!cold)
			return (EPERM);
		break;
	case MOD_UNLOAD:
		if (!cold && power_pm_get_type() == POWER_PM_TYPE_APM)
			return (EBUSY);
		break;
	default:
		break;
	}

	return (0);
}