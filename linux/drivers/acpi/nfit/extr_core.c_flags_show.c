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
typedef  int u16 ;
struct nvdimm {int dummy; } ;
struct nfit_mem {int /*<<< orphan*/  flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ACPI_NFIT_MEM_FLUSH_FAILED ; 
 int ACPI_NFIT_MEM_HEALTH_ENABLED ; 
 int ACPI_NFIT_MEM_HEALTH_OBSERVED ; 
 int ACPI_NFIT_MEM_MAP_FAILED ; 
 int ACPI_NFIT_MEM_NOT_ARMED ; 
 int ACPI_NFIT_MEM_RESTORE_FAILED ; 
 int ACPI_NFIT_MEM_SAVE_FAILED ; 
 int /*<<< orphan*/  NFIT_MEM_DIRTY ; 
 TYPE_1__* __to_nfit_memdev (struct nfit_mem*) ; 
 struct nfit_mem* nvdimm_provider_data (struct nvdimm*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

__attribute__((used)) static ssize_t flags_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm *nvdimm = to_nvdimm(dev);
	struct nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	u16 flags = __to_nfit_memdev(nfit_mem)->flags;

	if (test_bit(NFIT_MEM_DIRTY, &nfit_mem->flags))
		flags |= ACPI_NFIT_MEM_FLUSH_FAILED;

	return sprintf(buf, "%s%s%s%s%s%s%s\n",
		flags & ACPI_NFIT_MEM_SAVE_FAILED ? "save_fail " : "",
		flags & ACPI_NFIT_MEM_RESTORE_FAILED ? "restore_fail " : "",
		flags & ACPI_NFIT_MEM_FLUSH_FAILED ? "flush_fail " : "",
		flags & ACPI_NFIT_MEM_NOT_ARMED ? "not_armed " : "",
		flags & ACPI_NFIT_MEM_HEALTH_OBSERVED ? "smart_event " : "",
		flags & ACPI_NFIT_MEM_MAP_FAILED ? "map_fail " : "",
		flags & ACPI_NFIT_MEM_HEALTH_ENABLED ? "smart_notify " : "");
}