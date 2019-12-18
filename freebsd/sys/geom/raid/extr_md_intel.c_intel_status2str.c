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
#define  INTEL_S_DEGRADED 131 
#define  INTEL_S_FAILURE 130 
#define  INTEL_S_READY 129 
#define  INTEL_S_UNINITIALIZED 128 

__attribute__((used)) static char *
intel_status2str(int status)
{

	switch (status) {
	case INTEL_S_READY:
		return ("READY");
	case INTEL_S_UNINITIALIZED:
		return ("UNINITIALIZED");
	case INTEL_S_DEGRADED:
		return ("DEGRADED");
	case INTEL_S_FAILURE:
		return ("FAILURE");
	default:
		return ("UNKNOWN");
	}
}