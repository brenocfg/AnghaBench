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
typedef  int uint32_t ;

/* Variables and functions */
 int BDW_GMCH_GMS_MASK ; 
 int BDW_GMCH_GMS_SHIFT ; 
 int MiB (int) ; 
 int /*<<< orphan*/  SNB_GMCH_CTRL ; 
 int pci_cfgregread (int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static vm_paddr_t
intel_stolen_size_gen8(int bus, int slot, int func)
{
	uint32_t ctrl;
	vm_paddr_t val;

	ctrl = pci_cfgregread(bus, slot, func, SNB_GMCH_CTRL, 2);
	val = (ctrl >> BDW_GMCH_GMS_SHIFT) & BDW_GMCH_GMS_MASK;
	return (val * MiB(32));
}