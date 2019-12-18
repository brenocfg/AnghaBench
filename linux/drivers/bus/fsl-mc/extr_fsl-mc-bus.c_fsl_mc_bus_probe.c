#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {int of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mc_version {int /*<<< orphan*/  revision; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct fsl_mc_obj_desc {int id; int irq_count; scalar_t__ region_count; int /*<<< orphan*/  type; int /*<<< orphan*/  vendor; int /*<<< orphan*/  ver_minor; int /*<<< orphan*/  ver_major; } ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_device {int dummy; } ;
struct fsl_mc {struct fsl_mc_device* root_mc_bus_dev; int /*<<< orphan*/  num_translation_ranges; int /*<<< orphan*/  translation_ranges; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FSL_MC_IO_ATOMIC_CONTEXT_PORTAL ; 
 int /*<<< orphan*/  FSL_MC_VENDOR_FREESCALE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_mc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int dprc_get_api_version (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dprc_get_container_id (struct fsl_mc_io*,int /*<<< orphan*/ ,int*) ; 
 int fsl_create_mc_io (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsl_mc_io**) ; 
 int /*<<< orphan*/  fsl_destroy_mc_io (struct fsl_mc_io*) ; 
 int fsl_mc_device_add (struct fsl_mc_obj_desc*,struct fsl_mc_io*,TYPE_1__*,struct fsl_mc_device**) ; 
 int get_mc_addr_translation_ranges (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mc_get_version (struct fsl_mc_io*,int /*<<< orphan*/ ,struct mc_version*) ; 
 int /*<<< orphan*/  memset (struct fsl_mc_obj_desc*,int /*<<< orphan*/ ,int) ; 
 int of_address_to_resource (int,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fsl_mc*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fsl_mc_bus_probe(struct platform_device *pdev)
{
	struct fsl_mc_obj_desc obj_desc;
	int error;
	struct fsl_mc *mc;
	struct fsl_mc_device *mc_bus_dev = NULL;
	struct fsl_mc_io *mc_io = NULL;
	int container_id;
	phys_addr_t mc_portal_phys_addr;
	u32 mc_portal_size;
	struct mc_version mc_version;
	struct resource res;

	mc = devm_kzalloc(&pdev->dev, sizeof(*mc), GFP_KERNEL);
	if (!mc)
		return -ENOMEM;

	platform_set_drvdata(pdev, mc);

	/*
	 * Get physical address of MC portal for the root DPRC:
	 */
	error = of_address_to_resource(pdev->dev.of_node, 0, &res);
	if (error < 0) {
		dev_err(&pdev->dev,
			"of_address_to_resource() failed for %pOF\n",
			pdev->dev.of_node);
		return error;
	}

	mc_portal_phys_addr = res.start;
	mc_portal_size = resource_size(&res);
	error = fsl_create_mc_io(&pdev->dev, mc_portal_phys_addr,
				 mc_portal_size, NULL,
				 FSL_MC_IO_ATOMIC_CONTEXT_PORTAL, &mc_io);
	if (error < 0)
		return error;

	error = mc_get_version(mc_io, 0, &mc_version);
	if (error != 0) {
		dev_err(&pdev->dev,
			"mc_get_version() failed with error %d\n", error);
		goto error_cleanup_mc_io;
	}

	dev_info(&pdev->dev, "MC firmware version: %u.%u.%u\n",
		 mc_version.major, mc_version.minor, mc_version.revision);

	error = get_mc_addr_translation_ranges(&pdev->dev,
					       &mc->translation_ranges,
					       &mc->num_translation_ranges);
	if (error < 0)
		goto error_cleanup_mc_io;

	error = dprc_get_container_id(mc_io, 0, &container_id);
	if (error < 0) {
		dev_err(&pdev->dev,
			"dprc_get_container_id() failed: %d\n", error);
		goto error_cleanup_mc_io;
	}

	memset(&obj_desc, 0, sizeof(struct fsl_mc_obj_desc));
	error = dprc_get_api_version(mc_io, 0,
				     &obj_desc.ver_major,
				     &obj_desc.ver_minor);
	if (error < 0)
		goto error_cleanup_mc_io;

	obj_desc.vendor = FSL_MC_VENDOR_FREESCALE;
	strcpy(obj_desc.type, "dprc");
	obj_desc.id = container_id;
	obj_desc.irq_count = 1;
	obj_desc.region_count = 0;

	error = fsl_mc_device_add(&obj_desc, mc_io, &pdev->dev, &mc_bus_dev);
	if (error < 0)
		goto error_cleanup_mc_io;

	mc->root_mc_bus_dev = mc_bus_dev;
	return 0;

error_cleanup_mc_io:
	fsl_destroy_mc_io(mc_io);
	return error;
}