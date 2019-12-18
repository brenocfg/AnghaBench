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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {scalar_t__ om_start; int om_tte; int /*<<< orphan*/  om_size; } ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MAP_NOFAULT ; 
 int TD_V ; 
 int /*<<< orphan*/  VMFS_NO_SPACE ; 
 scalar_t__ VM_MAX_PROM_ADDRESS ; 
 scalar_t__ VM_MIN_PROM_ADDRESS ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* translations ; 
 int translations_size ; 
 int vm_map_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_init(void)
{
	vm_offset_t addr;
	vm_size_t size;
	int result;
	int i;

	for (i = 0; i < translations_size; i++) {
		addr = translations[i].om_start;
		size = translations[i].om_size;
		if ((translations[i].om_tte & TD_V) == 0)
			continue;
		if (addr < VM_MIN_PROM_ADDRESS || addr > VM_MAX_PROM_ADDRESS)
			continue;
		result = vm_map_find(kernel_map, NULL, 0, &addr, size, 0,
		    VMFS_NO_SPACE, VM_PROT_ALL, VM_PROT_ALL, MAP_NOFAULT);
		if (result != KERN_SUCCESS || addr != translations[i].om_start)
			panic("pmap_init: vm_map_find");
	}
}