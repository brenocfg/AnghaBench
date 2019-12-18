#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ modem_ready; } ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 scalar_t__ BSP_PPE32_SRST ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 TYPE_1__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_EnableCLK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_HaltArc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_IRQDisable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordRead (int,int*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWrite (int,int) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ LTQ_RCU_RST ; 
 int LTQ_RCU_RST_REQ_AFE ; 
 int LTQ_RCU_RST_REQ_DFE ; 
 int /*<<< orphan*/  MEI_SOFT_RESET ; 
 scalar_t__ ME_RST_CTRL ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_ResetARC (DSL_DEV_Device_t * pDev)
{
	u32 arc_debug_data = 0;

	IFX_MEI_HaltArc (pDev);

	IFX_MEI_LongWordRead ((u32) LTQ_RCU_RST, &arc_debug_data);
	IFX_MEI_LongWordWrite ((u32) LTQ_RCU_RST,
		arc_debug_data | LTQ_RCU_RST_REQ_DFE | LTQ_RCU_RST_REQ_AFE);

	// reset ARC
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_RST_CTRL, MEI_SOFT_RESET);
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_RST_CTRL, 0);

	IFX_MEI_IRQDisable (pDev);

	IFX_MEI_EnableCLK (pDev);

#if 0
	// reset part of PPE
	*(unsigned long *) (BSP_PPE32_SRST) = 0xC30;
	*(unsigned long *) (BSP_PPE32_SRST) = 0xFFF;
#endif

	DSL_DEV_PRIVATE(pDev)->modem_ready = 0;

	return DSL_DEV_MEI_ERR_SUCCESS;
}