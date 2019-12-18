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
typedef  scalar_t__ u32 ;
struct msi_desc {scalar_t__ irq; } ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_device {int flags; int /*<<< orphan*/  mc_handle; TYPE_1__** irqs; struct fsl_mc_io* mc_io; } ;
struct fsl_mc_bus {int /*<<< orphan*/  scan_mutex; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct msi_desc* msi_desc; } ;

/* Variables and functions */
 scalar_t__ DPRC_IRQ_EVENT_CONTAINER_DESTROYED ; 
 scalar_t__ DPRC_IRQ_EVENT_OBJ_ADDED ; 
 scalar_t__ DPRC_IRQ_EVENT_OBJ_CREATED ; 
 scalar_t__ DPRC_IRQ_EVENT_OBJ_DESTROYED ; 
 scalar_t__ DPRC_IRQ_EVENT_OBJ_REMOVED ; 
 int ENXIO ; 
 unsigned int FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS ; 
 int FSL_MC_IS_DPRC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int,unsigned int) ; 
 int dprc_clear_irq_status (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int dprc_get_irq_status (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int dprc_scan_objects (struct fsl_mc_device*,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct fsl_mc_bus* to_fsl_mc_bus (struct fsl_mc_device*) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 

__attribute__((used)) static irqreturn_t dprc_irq0_handler_thread(int irq_num, void *arg)
{
	int error;
	u32 status;
	struct device *dev = arg;
	struct fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	struct fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	struct fsl_mc_io *mc_io = mc_dev->mc_io;
	struct msi_desc *msi_desc = mc_dev->irqs[0]->msi_desc;

	dev_dbg(dev, "DPRC IRQ %d triggered on CPU %u\n",
		irq_num, smp_processor_id());

	if (!(mc_dev->flags & FSL_MC_IS_DPRC))
		return IRQ_HANDLED;

	mutex_lock(&mc_bus->scan_mutex);
	if (!msi_desc || msi_desc->irq != (u32)irq_num)
		goto out;

	status = 0;
	error = dprc_get_irq_status(mc_io, 0, mc_dev->mc_handle, 0,
				    &status);
	if (error < 0) {
		dev_err(dev,
			"dprc_get_irq_status() failed: %d\n", error);
		goto out;
	}

	error = dprc_clear_irq_status(mc_io, 0, mc_dev->mc_handle, 0,
				      status);
	if (error < 0) {
		dev_err(dev,
			"dprc_clear_irq_status() failed: %d\n", error);
		goto out;
	}

	if (status & (DPRC_IRQ_EVENT_OBJ_ADDED |
		      DPRC_IRQ_EVENT_OBJ_REMOVED |
		      DPRC_IRQ_EVENT_CONTAINER_DESTROYED |
		      DPRC_IRQ_EVENT_OBJ_DESTROYED |
		      DPRC_IRQ_EVENT_OBJ_CREATED)) {
		unsigned int irq_count;

		error = dprc_scan_objects(mc_dev, &irq_count);
		if (error < 0) {
			/*
			 * If the error is -ENXIO, we ignore it, as it indicates
			 * that the object scan was aborted, as we detected that
			 * an object was removed from the DPRC in the MC, while
			 * we were scanning the DPRC.
			 */
			if (error != -ENXIO) {
				dev_err(dev, "dprc_scan_objects() failed: %d\n",
					error);
			}

			goto out;
		}

		if (irq_count > FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS) {
			dev_warn(dev,
				 "IRQs needed (%u) exceed IRQs preallocated (%u)\n",
				 irq_count, FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS);
		}
	}

out:
	mutex_unlock(&mc_bus->scan_mutex);
	return IRQ_HANDLED;
}