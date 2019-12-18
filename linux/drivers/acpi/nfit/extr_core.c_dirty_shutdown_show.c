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
struct nvdimm {int dummy; } ;
struct nfit_mem {int dirty_shutdown; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct nfit_mem* nvdimm_provider_data (struct nvdimm*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

__attribute__((used)) static ssize_t dirty_shutdown_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm *nvdimm = to_nvdimm(dev);
	struct nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	return sprintf(buf, "%d\n", nfit_mem->dirty_shutdown);
}