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
typedef  int /*<<< orphan*/  u32 ;
struct dmi_system_id {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSR_IA32_THERM_CONTROL ; 
 int msr_build_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msr_initialize_bdw(const struct dmi_system_id *d)
{
	/* Add any extra MSR ids into this array. */
	u32 bdw_msr_id[] = { MSR_IA32_THERM_CONTROL };

	pr_info("x86/pm: %s detected, MSR saving is needed during suspending.\n", d->ident);
	return msr_build_context(bdw_msr_id, ARRAY_SIZE(bdw_msr_id));
}