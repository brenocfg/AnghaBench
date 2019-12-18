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
typedef  int u64 ;
struct TYPE_3__ {int address_lo; int address_hi; int /*<<< orphan*/  data; } ;
struct msi_desc {int /*<<< orphan*/  irq; TYPE_1__ msg; } ;
struct fsl_mc_device_irq {int /*<<< orphan*/  dev_irq_index; struct msi_desc* msi_desc; struct fsl_mc_device* mc_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; TYPE_2__ obj_desc; int /*<<< orphan*/  mc_handle; int /*<<< orphan*/  mc_io; } ;
struct dprc_irq_cfg {int paddr; int /*<<< orphan*/  irq_num; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int MC_CMD_FLAG_INTR_DIS ; 
 int MC_CMD_FLAG_PRI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dprc_set_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dprc_irq_cfg*) ; 
 int dprc_set_obj_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dprc_irq_cfg*) ; 

__attribute__((used)) static void __fsl_mc_msi_write_msg(struct fsl_mc_device *mc_bus_dev,
				   struct fsl_mc_device_irq *mc_dev_irq)
{
	int error;
	struct fsl_mc_device *owner_mc_dev = mc_dev_irq->mc_dev;
	struct msi_desc *msi_desc = mc_dev_irq->msi_desc;
	struct dprc_irq_cfg irq_cfg;

	/*
	 * msi_desc->msg.address is 0x0 when this function is invoked in
	 * the free_irq() code path. In this case, for the MC, we don't
	 * really need to "unprogram" the MSI, so we just return.
	 */
	if (msi_desc->msg.address_lo == 0x0 && msi_desc->msg.address_hi == 0x0)
		return;

	if (!owner_mc_dev)
		return;

	irq_cfg.paddr = ((u64)msi_desc->msg.address_hi << 32) |
			msi_desc->msg.address_lo;
	irq_cfg.val = msi_desc->msg.data;
	irq_cfg.irq_num = msi_desc->irq;

	if (owner_mc_dev == mc_bus_dev) {
		/*
		 * IRQ is for the mc_bus_dev's DPRC itself
		 */
		error = dprc_set_irq(mc_bus_dev->mc_io,
				     MC_CMD_FLAG_INTR_DIS | MC_CMD_FLAG_PRI,
				     mc_bus_dev->mc_handle,
				     mc_dev_irq->dev_irq_index,
				     &irq_cfg);
		if (error < 0) {
			dev_err(&owner_mc_dev->dev,
				"dprc_set_irq() failed: %d\n", error);
		}
	} else {
		/*
		 * IRQ is for for a child device of mc_bus_dev
		 */
		error = dprc_set_obj_irq(mc_bus_dev->mc_io,
					 MC_CMD_FLAG_INTR_DIS | MC_CMD_FLAG_PRI,
					 mc_bus_dev->mc_handle,
					 owner_mc_dev->obj_desc.type,
					 owner_mc_dev->obj_desc.id,
					 mc_dev_irq->dev_irq_index,
					 &irq_cfg);
		if (error < 0) {
			dev_err(&owner_mc_dev->dev,
				"dprc_obj_set_irq() failed: %d\n", error);
		}
	}
}