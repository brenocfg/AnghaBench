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
 int /*<<< orphan*/  X86_BUG_MONITOR ; 
 int /*<<< orphan*/  X86_FEATURE_ARAT ; 
 int /*<<< orphan*/  X86_FEATURE_MWAIT ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_cpu_has_bug (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool kvm_can_mwait_in_guest(void)
{
	return boot_cpu_has(X86_FEATURE_MWAIT) &&
		!boot_cpu_has_bug(X86_BUG_MONITOR) &&
		boot_cpu_has(X86_FEATURE_ARAT);
}