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
struct nfit_mem {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ NVDIMM_FAMILY_INTEL ; 
 int /*<<< orphan*/  nfit_intel_shutdown_status (struct nfit_mem*) ; 

__attribute__((used)) static void populate_shutdown_status(struct nfit_mem *nfit_mem)
{
	/*
	 * For DIMMs that provide a dynamic facility to retrieve a
	 * dirty-shutdown status and/or a dirty-shutdown count, cache
	 * these values in nfit_mem.
	 */
	if (nfit_mem->family == NVDIMM_FAMILY_INTEL)
		nfit_intel_shutdown_status(nfit_mem);
}