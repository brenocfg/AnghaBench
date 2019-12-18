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
typedef  enum mfi_pd_state { ____Placeholder_mfi_pd_state } mfi_pd_state ;

/* Variables and functions */
#define  MFI_PD_STATE_COPYBACK 136 
#define  MFI_PD_STATE_FAILED 135 
#define  MFI_PD_STATE_HOT_SPARE 134 
#define  MFI_PD_STATE_OFFLINE 133 
#define  MFI_PD_STATE_ONLINE 132 
#define  MFI_PD_STATE_REBUILD 131 
#define  MFI_PD_STATE_SYSTEM 130 
#define  MFI_PD_STATE_UNCONFIGURED_BAD 129 
#define  MFI_PD_STATE_UNCONFIGURED_GOOD 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
mfi_pdstate(enum mfi_pd_state state)
{
	static char buf[16];

	switch (state) {
	case MFI_PD_STATE_UNCONFIGURED_GOOD:
		return ("UNCONFIGURED GOOD");
	case MFI_PD_STATE_UNCONFIGURED_BAD:
		return ("UNCONFIGURED BAD");
	case MFI_PD_STATE_HOT_SPARE:
		return ("HOT SPARE");
	case MFI_PD_STATE_OFFLINE:
		return ("OFFLINE");
	case MFI_PD_STATE_FAILED:
		return ("FAILED");
	case MFI_PD_STATE_REBUILD:
		return ("REBUILD");
	case MFI_PD_STATE_ONLINE:
		return ("ONLINE");
	case MFI_PD_STATE_COPYBACK:
		return ("COPYBACK");
	case MFI_PD_STATE_SYSTEM:
		return ("JBOD");
	default:
		sprintf(buf, "PSTATE 0x%04x", state);
		return (buf);
	}
}