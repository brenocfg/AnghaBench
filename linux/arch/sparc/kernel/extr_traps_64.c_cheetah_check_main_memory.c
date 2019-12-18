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

/* Variables and functions */
 unsigned long PAGE_OFFSET ; 
 scalar_t__ high_memory ; 
 int kern_addr_valid (unsigned long) ; 

__attribute__((used)) static int cheetah_check_main_memory(unsigned long paddr)
{
	unsigned long vaddr = PAGE_OFFSET + paddr;

	if (vaddr > (unsigned long) high_memory)
		return 0;

	return kern_addr_valid(vaddr);
}