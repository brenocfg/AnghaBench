#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hw_perf_event_extra {scalar_t__ idx; int config; scalar_t__ reg; } ;
struct hw_perf_event {int config; scalar_t__ config_base; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct pci_dev {int dummy; } ;
struct intel_uncore_box {int dieid; TYPE_1__* pmu; struct pci_dev* pci_dev; } ;
struct TYPE_4__ {struct pci_dev** dev; } ;
struct TYPE_3__ {int pmu_idx; } ;

/* Variables and functions */
 scalar_t__ EXTRA_REG_NONE ; 
 int SNBEP_PCI_QPI_PORT0_FILTER ; 
 int SNBEP_PMON_CTL_EN ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 TYPE_2__* uncore_extra_pci_dev ; 

__attribute__((used)) static void snbep_qpi_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct pci_dev *pdev = box->pci_dev;
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	struct hw_perf_event_extra *reg2 = &hwc->branch_reg;

	if (reg1->idx != EXTRA_REG_NONE) {
		int idx = box->pmu->pmu_idx + SNBEP_PCI_QPI_PORT0_FILTER;
		int die = box->dieid;
		struct pci_dev *filter_pdev = uncore_extra_pci_dev[die].dev[idx];

		if (filter_pdev) {
			pci_write_config_dword(filter_pdev, reg1->reg,
						(u32)reg1->config);
			pci_write_config_dword(filter_pdev, reg1->reg + 4,
						(u32)(reg1->config >> 32));
			pci_write_config_dword(filter_pdev, reg2->reg,
						(u32)reg2->config);
			pci_write_config_dword(filter_pdev, reg2->reg + 4,
						(u32)(reg2->config >> 32));
		}
	}

	pci_write_config_dword(pdev, hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
}