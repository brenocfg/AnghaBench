#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tlbe_ref {int dummy; } ;
struct kvmppc_vcpu_e500 {TYPE_1__** gtlb_priv; } ;
struct kvm_book3e_206_tlb_entry {int dummy; } ;
struct TYPE_2__ {struct tlbe_ref ref; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct kvm_book3e_206_tlb_entry* get_entry (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_tlb_eaddr (struct kvm_book3e_206_tlb_entry*) ; 
 int get_tlb_raddr (struct kvm_book3e_206_tlb_entry*) ; 
 int kvmppc_e500_shadow_map (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int,struct kvm_book3e_206_tlb_entry*,int /*<<< orphan*/ ,struct kvm_book3e_206_tlb_entry*,struct tlbe_ref*) ; 
 int /*<<< orphan*/  write_stlbe (struct kvmppc_vcpu_e500*,struct kvm_book3e_206_tlb_entry*,struct kvm_book3e_206_tlb_entry*,int,int) ; 

__attribute__((used)) static int kvmppc_e500_tlb0_map(struct kvmppc_vcpu_e500 *vcpu_e500, int esel,
				struct kvm_book3e_206_tlb_entry *stlbe)
{
	struct kvm_book3e_206_tlb_entry *gtlbe;
	struct tlbe_ref *ref;
	int stlbsel = 0;
	int sesel = 0;
	int r;

	gtlbe = get_entry(vcpu_e500, 0, esel);
	ref = &vcpu_e500->gtlb_priv[0][esel].ref;

	r = kvmppc_e500_shadow_map(vcpu_e500, get_tlb_eaddr(gtlbe),
			get_tlb_raddr(gtlbe) >> PAGE_SHIFT,
			gtlbe, 0, stlbe, ref);
	if (r)
		return r;

	write_stlbe(vcpu_e500, gtlbe, stlbe, stlbsel, sesel);

	return 0;
}