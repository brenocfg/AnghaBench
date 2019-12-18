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
struct kvmppc_vcpu_e500 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_book3e_206_tlb_entry {int dummy; } ;
typedef  int gva_t ;
typedef  int gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  esel_of (unsigned int) ; 
 struct kvm_book3e_206_tlb_entry* get_entry (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_tlb_bytes (struct kvm_book3e_206_tlb_entry*) ; 
 int get_tlb_raddr (struct kvm_book3e_206_tlb_entry*) ; 
 int /*<<< orphan*/  tlbsel_of (unsigned int) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

gpa_t kvmppc_mmu_xlate(struct kvm_vcpu *vcpu, unsigned int index,
			gva_t eaddr)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	struct kvm_book3e_206_tlb_entry *gtlbe;
	u64 pgmask;

	gtlbe = get_entry(vcpu_e500, tlbsel_of(index), esel_of(index));
	pgmask = get_tlb_bytes(gtlbe) - 1;

	return get_tlb_raddr(gtlbe) | (eaddr & pgmask);
}