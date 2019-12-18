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
#define  PXA2XX_UDC_CMD_CONNECT 129 
#define  PXA2XX_UDC_CMD_DISCONNECT 128 
 int UP2OCR ; 
 int UP2OCR_DMPDE ; 
 int UP2OCR_DPPDE ; 
 int UP2OCR_DPPUE ; 
 int UP2OCR_HXOE ; 
 int UP2OCR_HXS ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void zeus_udc_command(int cmd)
{
	switch (cmd) {
	case PXA2XX_UDC_CMD_DISCONNECT:
		pr_info("zeus: disconnecting USB client\n");
		UP2OCR = UP2OCR_HXOE | UP2OCR_HXS | UP2OCR_DMPDE | UP2OCR_DPPDE;
		break;

	case PXA2XX_UDC_CMD_CONNECT:
		pr_info("zeus: connecting USB client\n");
		UP2OCR = UP2OCR_HXOE | UP2OCR_DPPUE;
		break;
	}
}