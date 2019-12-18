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
struct resource {char* name; int /*<<< orphan*/  desc; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct nd_region_desc {struct resource* res; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IORES_DESC_PERSISTENT_MEMORY ; 
 int REGION_INTERSECTS ; 
 int /*<<< orphan*/  acpi_nfit_remove_resource ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 struct resource* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int insert_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  iomem_resource ; 
 int region_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int acpi_nfit_insert_resource(struct acpi_nfit_desc *acpi_desc,
		struct nd_region_desc *ndr_desc)
{
	struct resource *res, *nd_res = ndr_desc->res;
	int is_pmem, ret;

	/* No operation if the region is already registered as PMEM */
	is_pmem = region_intersects(nd_res->start, resource_size(nd_res),
				IORESOURCE_MEM, IORES_DESC_PERSISTENT_MEMORY);
	if (is_pmem == REGION_INTERSECTS)
		return 0;

	res = devm_kzalloc(acpi_desc->dev, sizeof(*res), GFP_KERNEL);
	if (!res)
		return -ENOMEM;

	res->name = "Persistent Memory";
	res->start = nd_res->start;
	res->end = nd_res->end;
	res->flags = IORESOURCE_MEM;
	res->desc = IORES_DESC_PERSISTENT_MEMORY;

	ret = insert_resource(&iomem_resource, res);
	if (ret)
		return ret;

	ret = devm_add_action_or_reset(acpi_desc->dev,
					acpi_nfit_remove_resource,
					res);
	if (ret)
		return ret;

	return 0;
}