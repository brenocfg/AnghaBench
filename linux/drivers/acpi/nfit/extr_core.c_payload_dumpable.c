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
struct nfit_mem {scalar_t__ family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NFIT_SECURITY_DEBUG ; 
 int IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ NVDIMM_FAMILY_INTEL ; 
 unsigned int NVDIMM_INTEL_GET_SECURITY_STATE ; 
 unsigned int NVDIMM_INTEL_MASTER_SECURE_ERASE ; 
 struct nfit_mem* nvdimm_provider_data (struct nvdimm*) ; 

__attribute__((used)) static bool payload_dumpable(struct nvdimm *nvdimm, unsigned int func)
{
	struct nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	if (nfit_mem && nfit_mem->family == NVDIMM_FAMILY_INTEL
			&& func >= NVDIMM_INTEL_GET_SECURITY_STATE
			&& func <= NVDIMM_INTEL_MASTER_SECURE_ERASE)
		return IS_ENABLED(CONFIG_NFIT_SECURITY_DEBUG);
	return true;
}