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
typedef  int vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int X86BIOS_PAGE_SIZE ; 
 int howmany (size_t,int) ; 
 scalar_t__* x86bios_map ; 

__attribute__((used)) static void
x86bios_set_pages(vm_offset_t va, vm_paddr_t pa, size_t size)
{
	int i, j;

	for (i = pa / X86BIOS_PAGE_SIZE, j = 0;
	    j < howmany(size, X86BIOS_PAGE_SIZE); i++, j++)
		x86bios_map[i] = va + j * X86BIOS_PAGE_SIZE;
}