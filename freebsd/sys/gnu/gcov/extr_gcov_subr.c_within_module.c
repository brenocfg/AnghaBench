#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  module_t ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {size_t size; scalar_t__ address; } ;

/* Variables and functions */
 TYPE_1__* module_file (int /*<<< orphan*/ ) ; 

int
within_module(vm_offset_t addr, module_t mod)
{
	linker_file_t link_info;
	vm_offset_t mod_addr;
	size_t mod_size;

	link_info = module_file(mod);
	mod_addr = (vm_offset_t)link_info->address;
	mod_size = link_info->size;
	if (addr >= mod_addr && addr < mod_addr + mod_size)
		return (1);
	return (0);
}