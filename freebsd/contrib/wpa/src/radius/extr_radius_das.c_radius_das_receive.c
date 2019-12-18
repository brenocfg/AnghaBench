#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wpabuf {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct TYPE_8__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_4__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct radius_msg {int dummy; } ;
struct radius_hdr {int code; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {TYPE_1__ v4; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct radius_das_data {unsigned int time_window; int /*<<< orphan*/  sock; int /*<<< orphan*/  shared_secret_len; int /*<<< orphan*/  shared_secret; scalar_t__ require_event_timestamp; int /*<<< orphan*/  require_message_authenticator; TYPE_3__ client_addr; } ;
struct os_time {scalar_t__ sec; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ MSG_MSGDUMP ; 
 int /*<<< orphan*/  RADIUS_ATTR_EVENT_TIMESTAMP ; 
#define  RADIUS_CODE_COA_REQUEST 129 
#define  RADIUS_CODE_DISCONNECT_REQUEST 128 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_4__) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  os_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct radius_msg* radius_das_coa (struct radius_das_data*,struct radius_msg*,char*,int) ; 
 struct radius_msg* radius_das_disconnect (struct radius_das_data*,struct radius_msg*,char*,int) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  radius_msg_dump (struct radius_msg*) ; 
 scalar_t__ radius_msg_finish_das_resp (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radius_hdr*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 int radius_msg_get_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct wpabuf* radius_msg_get_buf (struct radius_msg*) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_parse (int /*<<< orphan*/ *,int) ; 
 scalar_t__ radius_msg_verify_das_req (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_debug_level ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void radius_das_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct radius_das_data *das = eloop_ctx;
	u8 buf[1500];
	union {
		struct sockaddr_storage ss;
		struct sockaddr_in sin;
#ifdef CONFIG_IPV6
		struct sockaddr_in6 sin6;
#endif /* CONFIG_IPV6 */
	} from;
	char abuf[50];
	int from_port = 0;
	socklen_t fromlen;
	int len;
	struct radius_msg *msg, *reply = NULL;
	struct radius_hdr *hdr;
	struct wpabuf *rbuf;
	u32 val;
	int res;
	struct os_time now;

	fromlen = sizeof(from);
	len = recvfrom(sock, buf, sizeof(buf), 0,
		       (struct sockaddr *) &from.ss, &fromlen);
	if (len < 0) {
		wpa_printf(MSG_ERROR, "DAS: recvfrom: %s", strerror(errno));
		return;
	}

	os_strlcpy(abuf, inet_ntoa(from.sin.sin_addr), sizeof(abuf));
	from_port = ntohs(from.sin.sin_port);

	wpa_printf(MSG_DEBUG, "DAS: Received %d bytes from %s:%d",
		   len, abuf, from_port);
	if (das->client_addr.u.v4.s_addr &&
	    das->client_addr.u.v4.s_addr != from.sin.sin_addr.s_addr) {
		wpa_printf(MSG_DEBUG, "DAS: Drop message from unknown client");
		return;
	}

	msg = radius_msg_parse(buf, len);
	if (msg == NULL) {
		wpa_printf(MSG_DEBUG, "DAS: Parsing incoming RADIUS packet "
			   "from %s:%d failed", abuf, from_port);
		return;
	}

	if (wpa_debug_level <= MSG_MSGDUMP)
		radius_msg_dump(msg);

	if (radius_msg_verify_das_req(msg, das->shared_secret,
				       das->shared_secret_len,
				       das->require_message_authenticator)) {
		wpa_printf(MSG_DEBUG,
			   "DAS: Invalid authenticator or Message-Authenticator in packet from %s:%d - drop",
			   abuf, from_port);
		goto fail;
	}

	os_get_time(&now);
	res = radius_msg_get_attr(msg, RADIUS_ATTR_EVENT_TIMESTAMP,
				  (u8 *) &val, 4);
	if (res == 4) {
		u32 timestamp = ntohl(val);
		if ((unsigned int) abs((int) (now.sec - timestamp)) >
		    das->time_window) {
			wpa_printf(MSG_DEBUG, "DAS: Unacceptable "
				   "Event-Timestamp (%u; local time %u) in "
				   "packet from %s:%d - drop",
				   timestamp, (unsigned int) now.sec,
				   abuf, from_port);
			goto fail;
		}
	} else if (das->require_event_timestamp) {
		wpa_printf(MSG_DEBUG, "DAS: Missing Event-Timestamp in packet "
			   "from %s:%d - drop", abuf, from_port);
		goto fail;
	}

	hdr = radius_msg_get_hdr(msg);

	switch (hdr->code) {
	case RADIUS_CODE_DISCONNECT_REQUEST:
		reply = radius_das_disconnect(das, msg, abuf, from_port);
		break;
	case RADIUS_CODE_COA_REQUEST:
		reply = radius_das_coa(das, msg, abuf, from_port);
		break;
	default:
		wpa_printf(MSG_DEBUG, "DAS: Unexpected RADIUS code %u in "
			   "packet from %s:%d",
			   hdr->code, abuf, from_port);
	}

	if (reply) {
		wpa_printf(MSG_DEBUG, "DAS: Reply to %s:%d", abuf, from_port);

		if (!radius_msg_add_attr_int32(reply,
					       RADIUS_ATTR_EVENT_TIMESTAMP,
					       now.sec)) {
			wpa_printf(MSG_DEBUG, "DAS: Failed to add "
				   "Event-Timestamp attribute");
		}

		if (radius_msg_finish_das_resp(reply, das->shared_secret,
					       das->shared_secret_len, hdr) <
		    0) {
			wpa_printf(MSG_DEBUG, "DAS: Failed to add "
				   "Message-Authenticator attribute");
		}

		if (wpa_debug_level <= MSG_MSGDUMP)
			radius_msg_dump(reply);

		rbuf = radius_msg_get_buf(reply);
		res = sendto(das->sock, wpabuf_head(rbuf),
			     wpabuf_len(rbuf), 0,
			     (struct sockaddr *) &from.ss, fromlen);
		if (res < 0) {
			wpa_printf(MSG_ERROR, "DAS: sendto(to %s:%d): %s",
				   abuf, from_port, strerror(errno));
		}
	}

fail:
	radius_msg_free(msg);
	radius_msg_free(reply);
}