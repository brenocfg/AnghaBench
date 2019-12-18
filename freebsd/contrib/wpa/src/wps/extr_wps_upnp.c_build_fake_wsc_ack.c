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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ENROLLEE_NONCE ; 
 int /*<<< orphan*/  ATTR_REGISTRAR_NONCE ; 
 int /*<<< orphan*/  UPNP_WPS_WLANEVENT_TYPE_EAP ; 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 int /*<<< orphan*/  WPS_WSC_ACK ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * build_fake_wsc_ack(void)
{
	struct wpabuf *msg = wpabuf_alloc(100);
	if (msg == NULL)
		return NULL;
	wpabuf_put_u8(msg, UPNP_WPS_WLANEVENT_TYPE_EAP);
	wpabuf_put_str(msg, "00:00:00:00:00:00");
	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_WSC_ACK)) {
		wpabuf_free(msg);
		return NULL;
	}
	/* Enrollee Nonce */
	wpabuf_put_be16(msg, ATTR_ENROLLEE_NONCE);
	wpabuf_put_be16(msg, WPS_NONCE_LEN);
	wpabuf_put(msg, WPS_NONCE_LEN);
	/* Registrar Nonce */
	wpabuf_put_be16(msg, ATTR_REGISTRAR_NONCE);
	wpabuf_put_be16(msg, WPS_NONCE_LEN);
	wpabuf_put(msg, WPS_NONCE_LEN);
	if (wps_build_wfa_ext(msg, 0, NULL, 0, 0)) {
		wpabuf_free(msg);
		return NULL;
	}
	return msg;
}