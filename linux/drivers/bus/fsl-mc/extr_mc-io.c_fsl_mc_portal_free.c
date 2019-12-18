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
struct fsl_mc_resource {scalar_t__ type; struct fsl_mc_device* data; } ;
struct fsl_mc_io {struct fsl_mc_device* dpmcp_dev; } ;
struct fsl_mc_device {int /*<<< orphan*/ * consumer_link; struct fsl_mc_resource* resource; } ;

/* Variables and functions */
 scalar_t__ FSL_MC_POOL_DPMCP ; 
 int /*<<< orphan*/  fsl_destroy_mc_io (struct fsl_mc_io*) ; 
 int /*<<< orphan*/  fsl_mc_resource_free (struct fsl_mc_resource*) ; 

void fsl_mc_portal_free(struct fsl_mc_io *mc_io)
{
	struct fsl_mc_device *dpmcp_dev;
	struct fsl_mc_resource *resource;

	/*
	 * Every mc_io obtained by calling fsl_mc_portal_allocate() is supposed
	 * to have a DPMCP object associated with.
	 */
	dpmcp_dev = mc_io->dpmcp_dev;

	resource = dpmcp_dev->resource;
	if (!resource || resource->type != FSL_MC_POOL_DPMCP)
		return;

	if (resource->data != dpmcp_dev)
		return;

	fsl_destroy_mc_io(mc_io);
	fsl_mc_resource_free(resource);

	dpmcp_dev->consumer_link = NULL;
}