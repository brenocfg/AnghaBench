#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int logical_proc_id; scalar_t__ x86_max_cores; } ;
struct TYPE_7__ {scalar_t__ num_boxes; } ;
struct TYPE_6__ {int num_boxes; } ;
struct TYPE_5__ {scalar_t__* dev; } ;

/* Variables and functions */
 size_t HSWEP_PCI_PCU_3 ; 
 TYPE_4__ boot_cpu_data ; 
 int /*<<< orphan*/  hswep_msr_uncores ; 
 TYPE_3__ hswep_uncore_cbox ; 
 TYPE_2__ hswep_uncore_sbox ; 
 int /*<<< orphan*/  pci_read_config_dword (scalar_t__,int,int*) ; 
 TYPE_1__* uncore_extra_pci_dev ; 
 int /*<<< orphan*/  uncore_msr_uncores ; 

void hswep_uncore_cpu_init(void)
{
	int pkg = boot_cpu_data.logical_proc_id;

	if (hswep_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		hswep_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;

	/* Detect 6-8 core systems with only two SBOXes */
	if (uncore_extra_pci_dev[pkg].dev[HSWEP_PCI_PCU_3]) {
		u32 capid4;

		pci_read_config_dword(uncore_extra_pci_dev[pkg].dev[HSWEP_PCI_PCU_3],
				      0x94, &capid4);
		if (((capid4 >> 6) & 0x3) == 0)
			hswep_uncore_sbox.num_boxes = 2;
	}

	uncore_msr_uncores = hswep_msr_uncores;
}