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
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_FAILURE ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_IRQDisable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_IRQEnable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_AdslMailboxIRQEnable (DSL_DEV_Device_t *pDev, int enable)
{
	DSL_DEV_MeiError_t meierr;
	switch (enable) {
	case 0:
		meierr = DSL_DEV_MEI_ERR_SUCCESS;
		IFX_MEI_IRQDisable (pDev);
		break;
	case 1:
		IFX_MEI_IRQEnable (pDev);
		meierr = DSL_DEV_MEI_ERR_SUCCESS;
		break;
	default:
		meierr = DSL_DEV_MEI_ERR_FAILURE;
		break;

	}
	return meierr;
}