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
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int ARC_AUX_HALT ; 
 int /*<<< orphan*/  AUX_STATUS ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_ControlModeSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_IRQEnable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JTAG_MASTER_MODE ; 
 int /*<<< orphan*/  MEI_DEBUG_DEC_AUX_MASK ; 
 int /*<<< orphan*/  MEI_MASTER_MODE ; 
 int /*<<< orphan*/  _IFX_MEI_DBGLongWordRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _IFX_MEI_DBGLongWordWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_RunArc (DSL_DEV_Device_t * pDev)
{
	u32 arc_debug_data = 0x0;

	//      Switch arc control from JTAG mode to MEI mode- write '1' to bit0
	IFX_MEI_ControlModeSet (pDev, MEI_MASTER_MODE);
	_IFX_MEI_DBGLongWordRead (pDev, MEI_DEBUG_DEC_AUX_MASK,
					AUX_STATUS, &arc_debug_data);

	//      Write debug data reg with content ANDd with 0xFDFFFFFF (halt bit cleared)
	arc_debug_data &= ~ARC_AUX_HALT;
	_IFX_MEI_DBGLongWordWrite (pDev, MEI_DEBUG_DEC_AUX_MASK,
					 AUX_STATUS, arc_debug_data);

	//      Switch arc control from MEI mode to JTAG mode- write '0' to bit0
	IFX_MEI_ControlModeSet (pDev, JTAG_MASTER_MODE);
	//      Enable mask for arc codeswap interrupts
	IFX_MEI_IRQEnable (pDev);

	return DSL_DEV_MEI_ERR_SUCCESS;

}