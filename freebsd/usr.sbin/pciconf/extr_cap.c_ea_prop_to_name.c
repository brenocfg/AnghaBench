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
typedef  int uint8_t ;

/* Variables and functions */
#define  PCIM_EA_P_BRIDGE_IO 138 
#define  PCIM_EA_P_BRIDGE_MEM 137 
#define  PCIM_EA_P_BRIDGE_MEM_PREFETCH 136 
#define  PCIM_EA_P_IO 135 
#define  PCIM_EA_P_IO_RESERVED 134 
#define  PCIM_EA_P_MEM 133 
#define  PCIM_EA_P_MEM_PREFETCH 132 
#define  PCIM_EA_P_MEM_RESERVED 131 
#define  PCIM_EA_P_UNAVAILABLE 130 
#define  PCIM_EA_P_VF_MEM 129 
#define  PCIM_EA_P_VF_MEM_PREFETCH 128 

__attribute__((used)) static const char *
ea_prop_to_name(uint8_t prop)
{

	switch (prop) {
	case PCIM_EA_P_MEM:
		return "Non-Prefetchable Memory";
	case PCIM_EA_P_MEM_PREFETCH:
		return "Prefetchable Memory";
	case PCIM_EA_P_IO:
		return "I/O Space";
	case PCIM_EA_P_VF_MEM_PREFETCH:
		return "VF Prefetchable Memory";
	case PCIM_EA_P_VF_MEM:
		return "VF Non-Prefetchable Memory";
	case PCIM_EA_P_BRIDGE_MEM:
		return "Bridge Non-Prefetchable Memory";
	case PCIM_EA_P_BRIDGE_MEM_PREFETCH:
		return "Bridge Prefetchable Memory";
	case PCIM_EA_P_BRIDGE_IO:
		return "Bridge I/O Space";
	case PCIM_EA_P_MEM_RESERVED:
		return "Reserved Memory";
	case PCIM_EA_P_IO_RESERVED:
		return "Reserved I/O Space";
	case PCIM_EA_P_UNAVAILABLE:
		return "Unavailable";
	default:
		return "Reserved";
	}
}