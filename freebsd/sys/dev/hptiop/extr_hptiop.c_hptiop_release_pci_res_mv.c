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
struct hpt_iop_hba {scalar_t__ bar2_res; int /*<<< orphan*/  bar2_rid; int /*<<< orphan*/  pcidev; scalar_t__ bar0_res; int /*<<< orphan*/  bar0_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hptiop_release_pci_res_mv(struct hpt_iop_hba *hba)
{
	if (hba->bar0_res)
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
			hba->bar0_rid, hba->bar0_res);
	if (hba->bar2_res)
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
			hba->bar2_rid, hba->bar2_res);
}