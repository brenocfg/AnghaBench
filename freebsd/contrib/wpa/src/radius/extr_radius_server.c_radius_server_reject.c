#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  access_rejects; } ;
struct radius_server_data {int /*<<< orphan*/  auth_sock; TYPE_1__ counters; } ;
struct radius_msg {int dummy; } ;
struct radius_hdr {int /*<<< orphan*/  authenticator; int /*<<< orphan*/  identifier; } ;
struct TYPE_4__ {int /*<<< orphan*/  access_rejects; } ;
struct radius_client {TYPE_2__ counters; int /*<<< orphan*/  shared_secret_len; scalar_t__ shared_secret; } ;
struct eap_hdr {int /*<<< orphan*/  length; scalar_t__ identifier; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  eapfail ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_FAILURE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ MSG_MSGDUMP ; 
 int /*<<< orphan*/  RADIUS_ATTR_PROXY_STATE ; 
 int /*<<< orphan*/  RADIUS_CODE_ACCESS_REJECT ; 
 int /*<<< orphan*/  RADIUS_DEBUG (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  host_to_be16 (int) ; 
 int /*<<< orphan*/  os_memset (struct eap_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_add_eap (struct radius_msg*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ radius_msg_copy_attr (struct radius_msg*,struct radius_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_dump (struct radius_msg*) ; 
 scalar_t__ radius_msg_finish_srv (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 struct wpabuf* radius_msg_get_buf (struct radius_msg*) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_debug_level ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int radius_server_reject(struct radius_server_data *data,
				struct radius_client *client,
				struct radius_msg *request,
				struct sockaddr *from, socklen_t fromlen,
				const char *from_addr, int from_port)
{
	struct radius_msg *msg;
	int ret = 0;
	struct eap_hdr eapfail;
	struct wpabuf *buf;
	struct radius_hdr *hdr = radius_msg_get_hdr(request);

	RADIUS_DEBUG("Reject invalid request from %s:%d",
		     from_addr, from_port);

	msg = radius_msg_new(RADIUS_CODE_ACCESS_REJECT, hdr->identifier);
	if (msg == NULL) {
		return -1;
	}

	os_memset(&eapfail, 0, sizeof(eapfail));
	eapfail.code = EAP_CODE_FAILURE;
	eapfail.identifier = 0;
	eapfail.length = host_to_be16(sizeof(eapfail));

	if (!radius_msg_add_eap(msg, (u8 *) &eapfail, sizeof(eapfail))) {
		RADIUS_DEBUG("Failed to add EAP-Message attribute");
	}

	if (radius_msg_copy_attr(msg, request, RADIUS_ATTR_PROXY_STATE) < 0) {
		RADIUS_DEBUG("Failed to copy Proxy-State attribute(s)");
		radius_msg_free(msg);
		return -1;
	}

	if (radius_msg_finish_srv(msg, (u8 *) client->shared_secret,
				  client->shared_secret_len,
				  hdr->authenticator) <
	    0) {
		RADIUS_DEBUG("Failed to add Message-Authenticator attribute");
	}

	if (wpa_debug_level <= MSG_MSGDUMP) {
		radius_msg_dump(msg);
	}

	data->counters.access_rejects++;
	client->counters.access_rejects++;
	buf = radius_msg_get_buf(msg);
	if (sendto(data->auth_sock, wpabuf_head(buf), wpabuf_len(buf), 0,
		   (struct sockaddr *) from, sizeof(*from)) < 0) {
		wpa_printf(MSG_INFO, "sendto[RADIUS SRV]: %s", strerror(errno));
		ret = -1;
	}

	radius_msg_free(msg);

	return ret;
}