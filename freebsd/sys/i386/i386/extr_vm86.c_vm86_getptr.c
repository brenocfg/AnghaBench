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
typedef  scalar_t__ vm_offset_t ;
typedef  int u_short ;
struct vm86context {int npages; TYPE_1__* pmap; } ;
struct TYPE_2__ {scalar_t__ kva; int pte_num; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 

int
vm86_getptr(struct vm86context *vmc, vm_offset_t kva, u_short *sel,
     u_short *off)
{
	int i;

	for (i = 0; i < vmc->npages; i++)
		if (kva >= vmc->pmap[i].kva &&
		    kva < vmc->pmap[i].kva + PAGE_SIZE) {
			*off = kva - vmc->pmap[i].kva;
			*sel = vmc->pmap[i].pte_num << 8;
			return (1);
		}
	return (0);
}