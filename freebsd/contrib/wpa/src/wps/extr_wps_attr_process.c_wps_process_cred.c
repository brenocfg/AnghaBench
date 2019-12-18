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
struct wps_parse_attr {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  network_key_len; int /*<<< orphan*/  network_key; int /*<<< orphan*/  network_key_idx; int /*<<< orphan*/  encr_type; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  network_idx; } ;
struct wps_credential {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_process_cred_auth_type (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_encr_type (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_mac_addr (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_network_idx (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_network_key (struct wps_credential*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_network_key_idx (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_ssid (struct wps_credential*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wps_workaround_cred_key (struct wps_credential*) ; 

int wps_process_cred(struct wps_parse_attr *attr,
		     struct wps_credential *cred)
{
	wpa_printf(MSG_DEBUG, "WPS: Process Credential");

	/* TODO: support multiple Network Keys */
	if (wps_process_cred_network_idx(cred, attr->network_idx) ||
	    wps_process_cred_ssid(cred, attr->ssid, attr->ssid_len) ||
	    wps_process_cred_auth_type(cred, attr->auth_type) ||
	    wps_process_cred_encr_type(cred, attr->encr_type) ||
	    wps_process_cred_network_key_idx(cred, attr->network_key_idx) ||
	    wps_process_cred_network_key(cred, attr->network_key,
					 attr->network_key_len) ||
	    wps_process_cred_mac_addr(cred, attr->mac_addr))
		return -1;

	return wps_workaround_cred_key(cred);
}