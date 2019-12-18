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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ LOAD_ELF ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ kboot_get_phys_load_segment () ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
kboot_loadaddr(u_int type, void *data, uint64_t addr)
{

	if (type == LOAD_ELF)
		addr = roundup(addr, PAGE_SIZE);
	else
		addr += kboot_get_phys_load_segment();

	return (addr);
}