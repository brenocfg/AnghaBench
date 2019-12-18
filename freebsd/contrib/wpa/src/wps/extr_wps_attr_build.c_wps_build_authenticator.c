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
typedef  int /*<<< orphan*/  u8 ;
struct wps_data {int /*<<< orphan*/  authkey; struct wpabuf* last_msg; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_AUTHENTICATOR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPS_AUTHENTICATOR_LEN ; 
 int /*<<< orphan*/  WPS_AUTHKEY_LEN ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int wps_build_authenticator(struct wps_data *wps, struct wpabuf *msg)
{
	u8 hash[SHA256_MAC_LEN];
	const u8 *addr[2];
	size_t len[2];

	if (wps->last_msg == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: Last message not available for "
			   "building authenticator");
		return -1;
	}

	/* Authenticator = HMAC-SHA256_AuthKey(M_prev || M_curr*)
	 * (M_curr* is M_curr without the Authenticator attribute)
	 */
	addr[0] = wpabuf_head(wps->last_msg);
	len[0] = wpabuf_len(wps->last_msg);
	addr[1] = wpabuf_head(msg);
	len[1] = wpabuf_len(msg);
	hmac_sha256_vector(wps->authkey, WPS_AUTHKEY_LEN, 2, addr, len, hash);

	wpa_printf(MSG_DEBUG, "WPS:  * Authenticator");
	wpabuf_put_be16(msg, ATTR_AUTHENTICATOR);
	wpabuf_put_be16(msg, WPS_AUTHENTICATOR_LEN);
	wpabuf_put_data(msg, hash, WPS_AUTHENTICATOR_LEN);

	return 0;
}