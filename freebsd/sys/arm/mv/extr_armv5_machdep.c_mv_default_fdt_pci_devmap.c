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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct devmap_entry {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */

int
mv_default_fdt_pci_devmap(phandle_t node, struct devmap_entry *devmap,
    vm_offset_t io_va, vm_offset_t mem_va)
{

	return (0);
}