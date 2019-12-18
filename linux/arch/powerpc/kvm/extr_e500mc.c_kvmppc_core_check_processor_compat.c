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
struct TYPE_2__ {int /*<<< orphan*/  cpu_name; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 TYPE_1__* cur_cpu_spec ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int kvmppc_core_check_processor_compat(void)
{
	int r;

	if (strcmp(cur_cpu_spec->cpu_name, "e500mc") == 0)
		r = 0;
	else if (strcmp(cur_cpu_spec->cpu_name, "e5500") == 0)
		r = 0;
#ifdef CONFIG_ALTIVEC
	/*
	 * Since guests have the privilege to enable AltiVec, we need AltiVec
	 * support in the host to save/restore their context.
	 * Don't use CPU_FTR_ALTIVEC to identify cores with AltiVec unit
	 * because it's cleared in the absence of CONFIG_ALTIVEC!
	 */
	else if (strcmp(cur_cpu_spec->cpu_name, "e6500") == 0)
		r = 0;
#endif
	else
		r = -ENOTSUPP;

	return r;
}