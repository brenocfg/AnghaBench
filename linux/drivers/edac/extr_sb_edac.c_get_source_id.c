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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct sbridge_pvt {TYPE_1__* sbridge_dev; TYPE_2__ info; int /*<<< orphan*/  pci_br0; int /*<<< orphan*/  pci_sad1; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  source_id; } ;

/* Variables and functions */
 scalar_t__ BROADWELL ; 
 scalar_t__ HASWELL ; 
 scalar_t__ KNIGHTS_LANDING ; 
 int /*<<< orphan*/  SAD_TARGET ; 
 int /*<<< orphan*/  SOURCE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOURCE_ID_KNL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_source_id(struct mem_ctl_info *mci)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	u32 reg;

	if (pvt->info.type == HASWELL || pvt->info.type == BROADWELL ||
	    pvt->info.type == KNIGHTS_LANDING)
		pci_read_config_dword(pvt->pci_sad1, SAD_TARGET, &reg);
	else
		pci_read_config_dword(pvt->pci_br0, SAD_TARGET, &reg);

	if (pvt->info.type == KNIGHTS_LANDING)
		pvt->sbridge_dev->source_id = SOURCE_ID_KNL(reg);
	else
		pvt->sbridge_dev->source_id = SOURCE_ID(reg);
}