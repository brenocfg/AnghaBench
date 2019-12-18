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
struct x86_cpu_id {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSR_AMD64_CPUID_FN_1 ; 
 int msr_build_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msr_save_cpuid_features(const struct x86_cpu_id *c)
{
	u32 cpuid_msr_id[] = {
		MSR_AMD64_CPUID_FN_1,
	};

	pr_info("x86/pm: family %#hx cpu detected, MSR saving is needed during suspending.\n",
		c->family);

	return msr_build_context(cpuid_msr_id, ARRAY_SIZE(cpuid_msr_id));
}