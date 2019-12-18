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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 unsigned long KVM_HPAGE_SIZE (int) ; 
 int PT_MAX_HUGEPAGE_LEVEL ; 
 int PT_PAGE_TABLE_LEVEL ; 
 unsigned long kvm_host_page_size (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int host_mapping_level(struct kvm *kvm, gfn_t gfn)
{
	unsigned long page_size;
	int i, ret = 0;

	page_size = kvm_host_page_size(kvm, gfn);

	for (i = PT_PAGE_TABLE_LEVEL; i <= PT_MAX_HUGEPAGE_LEVEL; ++i) {
		if (page_size >= KVM_HPAGE_SIZE(i))
			ret = i;
		else
			break;
	}

	return ret;
}