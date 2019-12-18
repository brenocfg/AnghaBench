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
struct nvdimm_security_ops {int dummy; } ;

/* Variables and functions */
#define  NVDIMM_FAMILY_INTEL 128 
 struct nvdimm_security_ops const* intel_security_ops ; 

__attribute__((used)) static const struct nvdimm_security_ops *acpi_nfit_get_security_ops(int family)
{
	switch (family) {
	case NVDIMM_FAMILY_INTEL:
		return intel_security_ops;
	default:
		return NULL;
	}
}