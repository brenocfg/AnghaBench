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
union kvm_mmu_extended_role {int cr0_pg; int cr4_pae; int cr4_smep; int cr4_smap; int cr4_pse; int cr4_pke; int cr4_la57; int valid; int /*<<< orphan*/  maxphyaddr; int /*<<< orphan*/  member_0; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_CR4_LA57 ; 
 int /*<<< orphan*/  X86_CR4_PKE ; 
 int /*<<< orphan*/  X86_CR4_SMAP ; 
 int /*<<< orphan*/  X86_CR4_SMEP ; 
 int /*<<< orphan*/  cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pse (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static union kvm_mmu_extended_role kvm_calc_mmu_role_ext(struct kvm_vcpu *vcpu)
{
	union kvm_mmu_extended_role ext = {0};

	ext.cr0_pg = !!is_paging(vcpu);
	ext.cr4_pae = !!is_pae(vcpu);
	ext.cr4_smep = !!kvm_read_cr4_bits(vcpu, X86_CR4_SMEP);
	ext.cr4_smap = !!kvm_read_cr4_bits(vcpu, X86_CR4_SMAP);
	ext.cr4_pse = !!is_pse(vcpu);
	ext.cr4_pke = !!kvm_read_cr4_bits(vcpu, X86_CR4_PKE);
	ext.cr4_la57 = !!kvm_read_cr4_bits(vcpu, X86_CR4_LA57);
	ext.maxphyaddr = cpuid_maxphyaddr(vcpu);

	ext.valid = 1;

	return ext;
}