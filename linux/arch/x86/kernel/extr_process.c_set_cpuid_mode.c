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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  X86_FEATURE_CPUID_FAULT ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_cpuid () ; 
 int /*<<< orphan*/  enable_cpuid () ; 

__attribute__((used)) static int set_cpuid_mode(struct task_struct *task, unsigned long cpuid_enabled)
{
	if (!boot_cpu_has(X86_FEATURE_CPUID_FAULT))
		return -ENODEV;

	if (cpuid_enabled)
		enable_cpuid();
	else
		disable_cpuid();

	return 0;
}