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
struct wps_credential {size_t ssid_len; size_t key_len; int /*<<< orphan*/  key; void* encr_type; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  ssid; } ;
struct hostapd_data {TYPE_1__* wps; } ;
typedef  int /*<<< orphan*/  cred ;
struct TYPE_2__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_AUTH_OPEN ; 
 int /*<<< orphan*/  WPS_AUTH_WPA2PSK ; 
 int /*<<< orphan*/  WPS_AUTH_WPAPSK ; 
 void* WPS_ENCR_AES ; 
 void* WPS_ENCR_NONE ; 
 void* WPS_ENCR_TKIP ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  os_memset (struct wps_credential*,int /*<<< orphan*/ ,int) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int wps_registrar_config_ap (int /*<<< orphan*/ ,struct wps_credential*) ; 

int hostapd_wps_config_ap(struct hostapd_data *hapd, const char *ssid,
			  const char *auth, const char *encr, const char *key)
{
	struct wps_credential cred;
	size_t len;

	os_memset(&cred, 0, sizeof(cred));

	len = os_strlen(ssid);
	if ((len & 1) || len > 2 * sizeof(cred.ssid) ||
	    hexstr2bin(ssid, cred.ssid, len / 2))
		return -1;
	cred.ssid_len = len / 2;

	if (os_strncmp(auth, "OPEN", 4) == 0)
		cred.auth_type = WPS_AUTH_OPEN;
	else if (os_strncmp(auth, "WPAPSK", 6) == 0)
		cred.auth_type = WPS_AUTH_WPAPSK;
	else if (os_strncmp(auth, "WPA2PSK", 7) == 0)
		cred.auth_type = WPS_AUTH_WPA2PSK;
	else
		return -1;

	if (encr) {
		if (os_strncmp(encr, "NONE", 4) == 0)
			cred.encr_type = WPS_ENCR_NONE;
		else if (os_strncmp(encr, "TKIP", 4) == 0)
			cred.encr_type = WPS_ENCR_TKIP;
		else if (os_strncmp(encr, "CCMP", 4) == 0)
			cred.encr_type = WPS_ENCR_AES;
		else
			return -1;
	} else
		cred.encr_type = WPS_ENCR_NONE;

	if (key) {
		len = os_strlen(key);
		if ((len & 1) || len > 2 * sizeof(cred.key) ||
		    hexstr2bin(key, cred.key, len / 2))
			return -1;
		cred.key_len = len / 2;
	}

	return wps_registrar_config_ap(hapd->wps->registrar, &cred);
}