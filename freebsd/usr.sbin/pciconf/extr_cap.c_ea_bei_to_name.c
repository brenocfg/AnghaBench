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
 int PCIM_EA_BEI_BAR_0 ; 
 int PCIM_EA_BEI_BAR_5 ; 
#define  PCIM_EA_BEI_BRIDGE 131 
#define  PCIM_EA_BEI_ENI 130 
#define  PCIM_EA_BEI_RESERVED 129 
#define  PCIM_EA_BEI_ROM 128 
 int PCIM_EA_BEI_VF_BAR_0 ; 
 int PCIM_EA_BEI_VF_BAR_5 ; 

__attribute__((used)) static const char *
ea_bei_to_name(int bei)
{
	static const char *barstr[] = {
		"BAR0", "BAR1", "BAR2", "BAR3", "BAR4", "BAR5"
	};
	static const char *vfbarstr[] = {
		"VFBAR0", "VFBAR1", "VFBAR2", "VFBAR3", "VFBAR4", "VFBAR5"
	};

	if ((bei >= PCIM_EA_BEI_BAR_0) && (bei <= PCIM_EA_BEI_BAR_5))
		return (barstr[bei - PCIM_EA_BEI_BAR_0]);
	if ((bei >= PCIM_EA_BEI_VF_BAR_0) && (bei <= PCIM_EA_BEI_VF_BAR_5))
		return (vfbarstr[bei - PCIM_EA_BEI_VF_BAR_0]);

	switch (bei) {
	case PCIM_EA_BEI_BRIDGE:
		return "BRIDGE";
	case PCIM_EA_BEI_ENI:
		return "ENI";
	case PCIM_EA_BEI_ROM:
		return "ROM";
	case PCIM_EA_BEI_RESERVED:
	default:
		return "RSVD";
	}
}