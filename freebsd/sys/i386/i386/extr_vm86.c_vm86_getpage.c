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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct vm86context {int npages; TYPE_1__* pmap; } ;
struct TYPE_2__ {int pte_num; int /*<<< orphan*/  kva; } ;

/* Variables and functions */

vm_offset_t
vm86_getpage(struct vm86context *vmc, int pagenum)
{
	int i;

	for (i = 0; i < vmc->npages; i++)
		if (vmc->pmap[i].pte_num == pagenum)
			return (vmc->pmap[i].kva);
	return (0);
}