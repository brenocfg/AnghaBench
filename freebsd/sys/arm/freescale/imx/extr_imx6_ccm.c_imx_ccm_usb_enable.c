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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CCGR_CLK_MODE_ALWAYS ; 
 int /*<<< orphan*/  CCM_CCGR6 ; 
 int RD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccm_sc ; 

void
imx_ccm_usb_enable(device_t _usbdev)
{

	/*
	 * For imx6, the USBOH3 clock gate is bits 0-1 of CCGR6, so no need for
	 * shifting and masking here, just set the low-order two bits to ALWAYS.
	 */
	WR4(ccm_sc, CCM_CCGR6, RD4(ccm_sc, CCM_CCGR6) | CCGR_CLK_MODE_ALWAYS);
}