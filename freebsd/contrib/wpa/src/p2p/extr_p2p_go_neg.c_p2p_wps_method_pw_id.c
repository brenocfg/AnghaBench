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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum p2p_wps_method { ____Placeholder_p2p_wps_method } p2p_wps_method ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PW_DEFAULT ; 
 int /*<<< orphan*/  DEV_PW_NFC_CONNECTION_HANDOVER ; 
 int /*<<< orphan*/  DEV_PW_P2PS_DEFAULT ; 
 int /*<<< orphan*/  DEV_PW_PUSHBUTTON ; 
 int /*<<< orphan*/  DEV_PW_REGISTRAR_SPECIFIED ; 
 int /*<<< orphan*/  DEV_PW_USER_SPECIFIED ; 
#define  WPS_NFC 132 
#define  WPS_P2PS 131 
#define  WPS_PBC 130 
#define  WPS_PIN_DISPLAY 129 
#define  WPS_PIN_KEYPAD 128 

u16 p2p_wps_method_pw_id(enum p2p_wps_method wps_method)
{
	switch (wps_method) {
	case WPS_PIN_DISPLAY:
		return DEV_PW_REGISTRAR_SPECIFIED;
	case WPS_PIN_KEYPAD:
		return DEV_PW_USER_SPECIFIED;
	case WPS_PBC:
		return DEV_PW_PUSHBUTTON;
	case WPS_NFC:
		return DEV_PW_NFC_CONNECTION_HANDOVER;
	case WPS_P2PS:
		return DEV_PW_P2PS_DEFAULT;
	default:
		return DEV_PW_DEFAULT;
	}
}