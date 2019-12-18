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
struct kvm_mips_callbacks {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  cpu_has_vz ; 
 struct kvm_mips_callbacks kvm_vz_callbacks ; 
 int pgd_reg ; 
 int /*<<< orphan*/  pr_info (char*) ; 

int kvm_mips_emulation_init(struct kvm_mips_callbacks **install_callbacks)
{
	if (!cpu_has_vz)
		return -ENODEV;

	/*
	 * VZ requires at least 2 KScratch registers, so it should have been
	 * possible to allocate pgd_reg.
	 */
	if (WARN(pgd_reg == -1,
		 "pgd_reg not allocated even though cpu_has_vz\n"))
		return -ENODEV;

	pr_info("Starting KVM with MIPS VZ extensions\n");

	*install_callbacks = &kvm_vz_callbacks;
	return 0;
}