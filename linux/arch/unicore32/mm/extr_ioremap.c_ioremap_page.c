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
struct mem_type {int /*<<< orphan*/  prot_pte; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int ioremap_page_range (unsigned long,scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 

int ioremap_page(unsigned long virt, unsigned long phys,
		 const struct mem_type *mtype)
{
	return ioremap_page_range(virt, virt + PAGE_SIZE, phys,
				  __pgprot(mtype->prot_pte));
}