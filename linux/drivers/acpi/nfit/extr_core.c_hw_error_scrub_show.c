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
struct nvdimm_bus_descriptor {int dummy; } ;
struct nvdimm_bus {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_nfit_desc {int scrub_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct acpi_nfit_desc* to_acpi_desc (struct nvdimm_bus_descriptor*) ; 
 struct nvdimm_bus_descriptor* to_nd_desc (struct nvdimm_bus*) ; 
 struct nvdimm_bus* to_nvdimm_bus (struct device*) ; 

__attribute__((used)) static ssize_t hw_error_scrub_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	struct nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	struct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	return sprintf(buf, "%d\n", acpi_desc->scrub_mode);
}