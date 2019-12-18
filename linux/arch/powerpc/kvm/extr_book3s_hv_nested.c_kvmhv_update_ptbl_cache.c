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
struct patb_entry {int /*<<< orphan*/  patb1; int /*<<< orphan*/  patb0; } ;
struct kvm_nested_guest {int l1_lpid; void* process_table; void* l1_gr_to_hr; struct kvm* l1_host; } ;
struct TYPE_2__ {int l1_ptcr; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  ptbl_entry ;

/* Variables and functions */
 int EFAULT ; 
 int PRTB_MASK ; 
 int PRTS_MASK ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int kvm_read_guest (struct kvm*,unsigned long,struct patb_entry*,int) ; 
 int /*<<< orphan*/  kvmhv_set_nested_ptbl (struct kvm_nested_guest*) ; 

__attribute__((used)) static void kvmhv_update_ptbl_cache(struct kvm_nested_guest *gp)
{
	int ret;
	struct patb_entry ptbl_entry;
	unsigned long ptbl_addr;
	struct kvm *kvm = gp->l1_host;

	ret = -EFAULT;
	ptbl_addr = (kvm->arch.l1_ptcr & PRTB_MASK) + (gp->l1_lpid << 4);
	if (gp->l1_lpid < (1ul << ((kvm->arch.l1_ptcr & PRTS_MASK) + 8)))
		ret = kvm_read_guest(kvm, ptbl_addr,
				     &ptbl_entry, sizeof(ptbl_entry));
	if (ret) {
		gp->l1_gr_to_hr = 0;
		gp->process_table = 0;
	} else {
		gp->l1_gr_to_hr = be64_to_cpu(ptbl_entry.patb0);
		gp->process_table = be64_to_cpu(ptbl_entry.patb1);
	}
	kvmhv_set_nested_ptbl(gp);
}