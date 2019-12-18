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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_HYPERVISOR ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ is_lbr_from (unsigned long) ; 
 int lbr_from_signext_quirk_wr (int) ; 
 scalar_t__ rdmsrl_safe (unsigned long,int*) ; 
 int /*<<< orphan*/  wrmsrl (unsigned long,int) ; 
 scalar_t__ wrmsrl_safe (unsigned long,int) ; 

__attribute__((used)) static bool check_msr(unsigned long msr, u64 mask)
{
	u64 val_old, val_new, val_tmp;

	/*
	 * Disable the check for real HW, so we don't
	 * mess with potentionaly enabled registers:
	 */
	if (!boot_cpu_has(X86_FEATURE_HYPERVISOR))
		return true;

	/*
	 * Read the current value, change it and read it back to see if it
	 * matches, this is needed to detect certain hardware emulators
	 * (qemu/kvm) that don't trap on the MSR access and always return 0s.
	 */
	if (rdmsrl_safe(msr, &val_old))
		return false;

	/*
	 * Only change the bits which can be updated by wrmsrl.
	 */
	val_tmp = val_old ^ mask;

	if (is_lbr_from(msr))
		val_tmp = lbr_from_signext_quirk_wr(val_tmp);

	if (wrmsrl_safe(msr, val_tmp) ||
	    rdmsrl_safe(msr, &val_new))
		return false;

	/*
	 * Quirk only affects validation in wrmsr(), so wrmsrl()'s value
	 * should equal rdmsrl()'s even with the quirk.
	 */
	if (val_new != val_tmp)
		return false;

	if (is_lbr_from(msr))
		val_old = lbr_from_signext_quirk_wr(val_old);

	/* Here it's sure that the MSR can be safely accessed.
	 * Restore the old value and return.
	 */
	wrmsrl(msr, val_old);

	return true;
}