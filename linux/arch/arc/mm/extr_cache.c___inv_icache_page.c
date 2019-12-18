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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __ic_line_inv_vaddr (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

void __inv_icache_page(phys_addr_t paddr, unsigned long vaddr)
{
	__ic_line_inv_vaddr(paddr, vaddr, PAGE_SIZE);
}