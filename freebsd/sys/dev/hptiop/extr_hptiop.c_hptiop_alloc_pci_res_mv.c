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
struct hpt_iopmv_regs {int dummy; } ;
struct hpt_iopmu_mv {int dummy; } ;
struct TYPE_3__ {struct hpt_iopmu_mv* mu; struct hpt_iopmv_regs* regs; } ;
struct TYPE_4__ {TYPE_1__ mv; } ;
struct hpt_iop_hba {int bar0_rid; int bar2_rid; int /*<<< orphan*/  pcidev; int /*<<< orphan*/ * bar2_res; int /*<<< orphan*/ * bar0_res; TYPE_2__ u; void* bar2h; void* bar2t; void* bar0h; void* bar0t; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hptiop_alloc_pci_res_mv(struct hpt_iop_hba *hba)
{
	hba->bar0_rid = 0x10;
	hba->bar0_res = bus_alloc_resource_any(hba->pcidev,
			SYS_RES_MEMORY, &hba->bar0_rid, RF_ACTIVE);

	if (hba->bar0_res == NULL) {
		device_printf(hba->pcidev, "failed to get iop bar0.\n");
		return -1;
	}
	hba->bar0t = rman_get_bustag(hba->bar0_res);
	hba->bar0h = rman_get_bushandle(hba->bar0_res);
	hba->u.mv.regs = (struct hpt_iopmv_regs *)
				rman_get_virtual(hba->bar0_res);

	if (!hba->u.mv.regs) {
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
					hba->bar0_rid, hba->bar0_res);
		device_printf(hba->pcidev, "alloc bar0 mem res failed\n");
		return -1;
	}

	hba->bar2_rid = 0x18;
	hba->bar2_res = bus_alloc_resource_any(hba->pcidev,
			SYS_RES_MEMORY, &hba->bar2_rid, RF_ACTIVE);

	if (hba->bar2_res == NULL) {
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
					hba->bar0_rid, hba->bar0_res);
		device_printf(hba->pcidev, "failed to get iop bar2.\n");
		return -1;
	}

	hba->bar2t = rman_get_bustag(hba->bar2_res);
	hba->bar2h = rman_get_bushandle(hba->bar2_res);
	hba->u.mv.mu = (struct hpt_iopmu_mv *)rman_get_virtual(hba->bar2_res);

	if (!hba->u.mv.mu) {
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
					hba->bar0_rid, hba->bar0_res);
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
					hba->bar2_rid, hba->bar2_res);
		device_printf(hba->pcidev, "alloc mem bar2 res failed\n");
		return -1;
	}

	return 0;
}