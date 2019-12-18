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

/* Variables and functions */
#define  INTEL_CNGST_MASTER_MISSING 130 
#define  INTEL_CNGST_NEEDS_UPDATE 129 
#define  INTEL_CNGST_UPDATED 128 

__attribute__((used)) static char *
intel_cngst2str(int cng_state)
{

	switch (cng_state) {
	case INTEL_CNGST_UPDATED:
		return ("UPDATED");
	case INTEL_CNGST_NEEDS_UPDATE:
		return ("NEEDS_UPDATE");
	case INTEL_CNGST_MASTER_MISSING:
		return ("MASTER_MISSING");
	default:
		return ("UNKNOWN");
	}
}