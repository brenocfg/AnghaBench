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
struct fsl_mc_device {int /*<<< orphan*/ * consumer_link; struct fsl_mc_resource* resource; } ;

/* Variables and functions */
 scalar_t__ FSL_MC_POOL_DPMCP ; 
 int /*<<< orphan*/  fsl_mc_resource_free (struct fsl_mc_resource*) ; 

void fsl_mc_object_free(struct fsl_mc_device *mc_adev)
{
	struct fsl_mc_resource *resource;

	resource = mc_adev->resource;
	if (resource->type == FSL_MC_POOL_DPMCP)
		return;
	if (resource->data != mc_adev)
		return;

	fsl_mc_resource_free(resource);

	mc_adev->consumer_link = NULL;
}