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
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mc_handle; struct fsl_mc_io* mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dprc_clear_irq_status (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dprc_set_irq_enable (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dprc_set_irq_mask (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int disable_dprc_irq(struct fsl_mc_device *mc_dev)
{
	int error;
	struct fsl_mc_io *mc_io = mc_dev->mc_io;

	/*
	 * Disable generation of interrupt, while we configure it:
	 */
	error = dprc_set_irq_enable(mc_io, 0, mc_dev->mc_handle, 0, 0);
	if (error < 0) {
		dev_err(&mc_dev->dev,
			"Disabling DPRC IRQ failed: dprc_set_irq_enable() failed: %d\n",
			error);
		return error;
	}

	/*
	 * Disable all interrupt causes for the interrupt:
	 */
	error = dprc_set_irq_mask(mc_io, 0, mc_dev->mc_handle, 0, 0x0);
	if (error < 0) {
		dev_err(&mc_dev->dev,
			"Disabling DPRC IRQ failed: dprc_set_irq_mask() failed: %d\n",
			error);
		return error;
	}

	/*
	 * Clear any leftover interrupts:
	 */
	error = dprc_clear_irq_status(mc_io, 0, mc_dev->mc_handle, 0, ~0x0U);
	if (error < 0) {
		dev_err(&mc_dev->dev,
			"Disabling DPRC IRQ failed: dprc_clear_irq_status() failed: %d\n",
			error);
		return error;
	}

	return 0;
}