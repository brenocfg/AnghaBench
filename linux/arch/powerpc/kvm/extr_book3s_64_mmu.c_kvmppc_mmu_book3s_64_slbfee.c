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
typedef  int /*<<< orphan*/  ulong ;
struct kvmppc_slb {int /*<<< orphan*/  origv; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int ENOENT ; 
 struct kvmppc_slb* kvmppc_mmu_book3s_64_find_slbe (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_mmu_book3s_64_slbfee(struct kvm_vcpu *vcpu, gva_t eaddr,
				       ulong *ret_slb)
{
	struct kvmppc_slb *slbe = kvmppc_mmu_book3s_64_find_slbe(vcpu, eaddr);

	if (slbe) {
		*ret_slb = slbe->origv;
		return 0;
	}
	*ret_slb = 0;
	return -ENOENT;
}