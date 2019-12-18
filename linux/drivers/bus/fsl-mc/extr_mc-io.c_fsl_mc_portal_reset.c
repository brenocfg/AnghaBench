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
struct fsl_mc_io {struct fsl_mc_device* dpmcp_dev; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mc_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dpmcp_reset (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fsl_mc_portal_reset(struct fsl_mc_io *mc_io)
{
	int error;
	struct fsl_mc_device *dpmcp_dev = mc_io->dpmcp_dev;

	error = dpmcp_reset(mc_io, 0, dpmcp_dev->mc_handle);
	if (error < 0) {
		dev_err(&dpmcp_dev->dev, "dpmcp_reset() failed: %d\n", error);
		return error;
	}

	return 0;
}