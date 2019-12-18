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
struct prtb_entry {int /*<<< orphan*/  prtb0; } ;
struct kvmppc_pte {int dummy; } ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int EINVAL ; 
 int PRTB_MASK ; 
 int PRTS_MASK ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int kvm_read_guest (struct kvm*,unsigned long,struct prtb_entry*,int) ; 
 int kvmppc_mmu_walk_radix_tree (struct kvm_vcpu*,int /*<<< orphan*/ ,struct kvmppc_pte*,unsigned long,int*) ; 

int kvmppc_mmu_radix_translate_table(struct kvm_vcpu *vcpu, gva_t eaddr,
				     struct kvmppc_pte *gpte, u64 table,
				     int table_index, u64 *pte_ret_p)
{
	struct kvm *kvm = vcpu->kvm;
	int ret;
	unsigned long size, ptbl, root;
	struct prtb_entry entry;

	if ((table & PRTS_MASK) > 24)
		return -EINVAL;
	size = 1ul << ((table & PRTS_MASK) + 12);

	/* Is the table big enough to contain this entry? */
	if ((table_index * sizeof(entry)) >= size)
		return -EINVAL;

	/* Read the table to find the root of the radix tree */
	ptbl = (table & PRTB_MASK) + (table_index * sizeof(entry));
	ret = kvm_read_guest(kvm, ptbl, &entry, sizeof(entry));
	if (ret)
		return ret;

	/* Root is stored in the first double word */
	root = be64_to_cpu(entry.prtb0);

	return kvmppc_mmu_walk_radix_tree(vcpu, eaddr, gpte, root, pte_ret_p);
}