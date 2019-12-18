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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_DBG_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ARM_DEBUG_ARCH_V6 ; 
 int /*<<< orphan*/  c0 ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int read_cpuid_id () ; 

__attribute__((used)) static u8 get_debug_arch(void)
{
	u32 didr;

	/* Do we implement the extended CPUID interface? */
	if (((read_cpuid_id() >> 16) & 0xf) != 0xf) {
		pr_warn_once("CPUID feature registers not supported. "
			     "Assuming v6 debug is present.\n");
		return ARM_DEBUG_ARCH_V6;
	}

	ARM_DBG_READ(c0, c0, 0, didr);
	return (didr >> 16) & 0xf;
}