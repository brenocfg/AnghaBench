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
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DETECT ; 
 int /*<<< orphan*/  ANADIG_USB2_CHRG_DETECT ; 
 int BM_ANADIG_USB_CHRG_DETECT_CHK_CHRG_B ; 
 int BM_ANADIG_USB_CHRG_DETECT_EN_B ; 
 int /*<<< orphan*/  anatop ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imx_anatop_usb_chrg_detect_disable(void)
{
	regmap_write(anatop, ANADIG_USB1_CHRG_DETECT,
		BM_ANADIG_USB_CHRG_DETECT_EN_B
		| BM_ANADIG_USB_CHRG_DETECT_CHK_CHRG_B);
	regmap_write(anatop, ANADIG_USB2_CHRG_DETECT,
		BM_ANADIG_USB_CHRG_DETECT_EN_B |
		BM_ANADIG_USB_CHRG_DETECT_CHK_CHRG_B);
}