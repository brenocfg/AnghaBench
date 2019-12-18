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
struct wps_credential {int /*<<< orphan*/  mac_addr; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ wps_build_cred_auth_type (struct wpabuf*,struct wps_credential const*) ; 
 scalar_t__ wps_build_cred_encr_type (struct wpabuf*,struct wps_credential const*) ; 
 scalar_t__ wps_build_cred_network_idx (struct wpabuf*,struct wps_credential const*) ; 
 scalar_t__ wps_build_cred_network_key (struct wpabuf*,struct wps_credential const*) ; 
 scalar_t__ wps_build_cred_ssid (struct wpabuf*,struct wps_credential const*) ; 
 scalar_t__ wps_build_mac_addr (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_build_credential(struct wpabuf *msg,
				const struct wps_credential *cred)
{
	if (wps_build_cred_network_idx(msg, cred) ||
	    wps_build_cred_ssid(msg, cred) ||
	    wps_build_cred_auth_type(msg, cred) ||
	    wps_build_cred_encr_type(msg, cred) ||
	    wps_build_cred_network_key(msg, cred) ||
	    wps_build_mac_addr(msg, cred->mac_addr))
		return -1;
	return 0;
}