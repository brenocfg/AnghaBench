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
typedef  int u32 ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int HOST_MSTR ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,int) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordReadOffset (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int,int) ; 
#define  JTAG_MASTER_MODE 129 
#define  MEI_MASTER_MODE 128 
 scalar_t__ ME_DBG_MASTER ; 

__attribute__((used)) static void
IFX_MEI_ControlModeSet (DSL_DEV_Device_t * pDev, int mode)
{
	u32 temp = 0x0;

	IFX_MEI_LongWordReadOffset (pDev, (u32) ME_DBG_MASTER, &temp);
	switch (mode) {
	case JTAG_MASTER_MODE:
		temp &= ~(HOST_MSTR);
		break;
	case MEI_MASTER_MODE:
		temp |= (HOST_MSTR);
		break;
	default:
		IFX_MEI_EMSG ("IFX_MEI_ControlModeSet: unkonwn mode [%d]\n", mode);
		return;
	}
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_DBG_MASTER, temp);
}