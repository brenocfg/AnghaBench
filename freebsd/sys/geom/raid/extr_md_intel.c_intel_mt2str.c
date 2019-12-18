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
#define  INTEL_MT_GEN_MIGR 133 
#define  INTEL_MT_INIT 132 
#define  INTEL_MT_REBUILD 131 
#define  INTEL_MT_REPAIR 130 
#define  INTEL_MT_STATE_CHANGE 129 
#define  INTEL_MT_VERIFY 128 

__attribute__((used)) static char *
intel_mt2str(int type)
{

	switch (type) {
	case INTEL_MT_INIT:
		return ("INIT");
	case INTEL_MT_REBUILD:
		return ("REBUILD");
	case INTEL_MT_VERIFY:
		return ("VERIFY");
	case INTEL_MT_GEN_MIGR:
		return ("GEN_MIGR");
	case INTEL_MT_STATE_CHANGE:
		return ("STATE_CHANGE");
	case INTEL_MT_REPAIR:
		return ("REPAIR");
	default:
		return ("UNKNOWN");
	}
}