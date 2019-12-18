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
typedef  int /*<<< orphan*/  uint64_t ;
struct vm_guest_paging {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  ctx ; 
 int guest_paging_info (int,struct vm_guest_paging*) ; 
 int vm_gla2gpa_nofault (int /*<<< orphan*/ ,int,struct vm_guest_paging*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
guest_vaddr2paddr(int vcpu, uint64_t vaddr, uint64_t *paddr)
{
	struct vm_guest_paging paging;
	int fault;

	if (guest_paging_info(vcpu, &paging) == -1)
		return (-1);

	/*
	 * Always use PROT_READ.  We really care if the VA is
	 * accessible, not if the current vCPU can write.
	 */
	if (vm_gla2gpa_nofault(ctx, vcpu, &paging, vaddr, PROT_READ, paddr,
	    &fault) == -1)
		return (-1);
	if (fault)
		return (0);
	return (1);
}