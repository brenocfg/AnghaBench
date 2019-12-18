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
typedef  enum wps_error_indication { ____Placeholder_wps_error_indication } wps_error_indication ;

/* Variables and functions */
#define  WPS_EI_AUTH_FAILURE 131 
#define  WPS_EI_NO_ERROR 130 
#define  WPS_EI_SECURITY_TKIP_ONLY_PROHIBITED 129 
#define  WPS_EI_SECURITY_WEP_PROHIBITED 128 

const char * wps_ei_str(enum wps_error_indication ei)
{
	switch (ei) {
	case WPS_EI_NO_ERROR:
		return "No Error";
	case WPS_EI_SECURITY_TKIP_ONLY_PROHIBITED:
		return "TKIP Only Prohibited";
	case WPS_EI_SECURITY_WEP_PROHIBITED:
		return "WEP Prohibited";
	case WPS_EI_AUTH_FAILURE:
		return "Authentication Failure";
	default:
		return "Unknown";
	}
}