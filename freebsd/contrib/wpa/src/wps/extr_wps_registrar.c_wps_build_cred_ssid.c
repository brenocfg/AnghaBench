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
struct wps_credential {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SSID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_build_cred_ssid(struct wpabuf *msg,
			       const struct wps_credential *cred)
{
	wpa_printf(MSG_DEBUG, "WPS:  * SSID");
	wpa_hexdump_ascii(MSG_DEBUG, "WPS: SSID for Credential",
			  cred->ssid, cred->ssid_len);
	wpabuf_put_be16(msg, ATTR_SSID);
	wpabuf_put_be16(msg, cred->ssid_len);
	wpabuf_put_data(msg, cred->ssid, cred->ssid_len);
	return 0;
}