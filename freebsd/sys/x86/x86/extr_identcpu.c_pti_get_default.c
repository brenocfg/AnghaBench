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
 int /*<<< orphan*/  AMD_VENDOR_ID ; 
 int IA32_ARCH_CAP_RDCL_NO ; 
 int cpu_ia32_arch_caps ; 
 int /*<<< orphan*/  cpu_vendor ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pti_get_default(void)
{

	if (strcmp(cpu_vendor, AMD_VENDOR_ID) == 0)
		return (0);
	if ((cpu_ia32_arch_caps & IA32_ARCH_CAP_RDCL_NO) != 0)
		return (0);
	return (1);
}