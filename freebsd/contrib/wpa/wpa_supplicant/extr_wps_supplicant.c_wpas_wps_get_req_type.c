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
struct wpa_ssid {int /*<<< orphan*/  eap; } ;
typedef  enum wps_request_type { ____Placeholder_wps_request_type } wps_request_type ;

/* Variables and functions */
 int WPS_REQ_ENROLLEE ; 
 int WPS_REQ_REGISTRAR ; 
 scalar_t__ eap_is_wps_pbc_enrollee (int /*<<< orphan*/ *) ; 
 scalar_t__ eap_is_wps_pin_enrollee (int /*<<< orphan*/ *) ; 

enum wps_request_type wpas_wps_get_req_type(struct wpa_ssid *ssid)
{
	if (eap_is_wps_pbc_enrollee(&ssid->eap) ||
	    eap_is_wps_pin_enrollee(&ssid->eap))
		return WPS_REQ_ENROLLEE;
	else
		return WPS_REQ_REGISTRAR;
}