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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  u_short ;
struct vm86context {int npages; TYPE_1__* pmap; } ;
struct TYPE_2__ {int pte_num; int kva; } ;

/* Variables and functions */
 scalar_t__ MAKE_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 

vm_offset_t
vm86_getaddr(struct vm86context *vmc, u_short sel, u_short off)
{
	int i, page;
	vm_offset_t addr;

	addr = (vm_offset_t)MAKE_ADDR(sel, off);
	page = addr >> PAGE_SHIFT;
	for (i = 0; i < vmc->npages; i++)
		if (page == vmc->pmap[i].pte_num)
			return (vmc->pmap[i].kva + (addr & PAGE_MASK));
	return (0);
}