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
typedef  enum p2p_wps_method { ____Placeholder_p2p_wps_method } p2p_wps_method ;

/* Variables and functions */
#define  WPS_NFC 132 
#define  WPS_P2PS 131 
#define  WPS_PBC 130 
#define  WPS_PIN_DISPLAY 129 
#define  WPS_PIN_KEYPAD 128 

__attribute__((used)) static const char * p2p_wps_method_str(enum p2p_wps_method wps_method)
{
	switch (wps_method) {
	case WPS_PIN_DISPLAY:
		return "Display";
	case WPS_PIN_KEYPAD:
		return "Keypad";
	case WPS_PBC:
		return "PBC";
	case WPS_NFC:
		return "NFC";
	case WPS_P2PS:
		return "P2PS";
	default:
		return "??";
	}
}