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
typedef  enum mfi_ld_state { ____Placeholder_mfi_ld_state } mfi_ld_state ;

/* Variables and functions */
#define  MFI_LD_STATE_DEGRADED 131 
#define  MFI_LD_STATE_OFFLINE 130 
#define  MFI_LD_STATE_OPTIMAL 129 
#define  MFI_LD_STATE_PARTIALLY_DEGRADED 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
mfi_ldstate(enum mfi_ld_state state)
{
	static char buf[16];

	switch (state) {
	case MFI_LD_STATE_OFFLINE:
		return ("OFFLINE");
	case MFI_LD_STATE_PARTIALLY_DEGRADED:
		return ("PARTIALLY DEGRADED");
	case MFI_LD_STATE_DEGRADED:
		return ("DEGRADED");
	case MFI_LD_STATE_OPTIMAL:
		return ("OPTIMAL");
	default:
		sprintf(buf, "LSTATE 0x%02x", state);
		return (buf);
	}
}