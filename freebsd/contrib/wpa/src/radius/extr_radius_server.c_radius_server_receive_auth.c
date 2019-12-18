#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bad_authenticators; int /*<<< orphan*/  access_requests; int /*<<< orphan*/  unknown_types; int /*<<< orphan*/  malformed_access_requests; int /*<<< orphan*/  invalid_requests; } ;
struct radius_server_data {TYPE_1__ counters; scalar_t__ ipv6; } ;
struct radius_msg {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bad_authenticators; int /*<<< orphan*/  access_requests; int /*<<< orphan*/  unknown_types; int /*<<< orphan*/  malformed_access_requests; } ;
struct radius_client {TYPE_2__ counters; int /*<<< orphan*/  shared_secret_len; scalar_t__ shared_secret; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  abuf ;
struct TYPE_6__ {char* code; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ MSG_MSGDUMP ; 
 char* RADIUS_CODE_ACCESS_REQUEST ; 
 char* RADIUS_CODE_COA_ACK ; 
 char* RADIUS_CODE_COA_NAK ; 
 char* RADIUS_CODE_DISCONNECT_ACK ; 
 char* RADIUS_CODE_DISCONNECT_NAK ; 
 int /*<<< orphan*/  RADIUS_DEBUG (char*,...) ; 
 int /*<<< orphan*/  RADIUS_DUMP (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RADIUS_MAX_MSG_LEN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_dump (struct radius_msg*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 TYPE_3__* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_parse (int /*<<< orphan*/ *,int) ; 
 scalar_t__ radius_msg_verify_msg_auth (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct radius_client* radius_server_get_client (struct radius_server_data*,struct in_addr*,int) ; 
 int /*<<< orphan*/  radius_server_receive_coa_resp (struct radius_server_data*,struct radius_client*,struct radius_msg*,int) ; 
 int /*<<< orphan*/  radius_server_receive_disconnect_resp (struct radius_server_data*,struct radius_client*,struct radius_msg*,int) ; 
 int radius_server_request (struct radius_server_data*,struct radius_msg*,struct sockaddr*,int,struct radius_client*,char*,int,int /*<<< orphan*/ *) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_debug_level ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radius_server_receive_auth(int sock, void *eloop_ctx,
				       void *sock_ctx)
{
	struct radius_server_data *data = eloop_ctx;
	u8 *buf = NULL;
	union {
		struct sockaddr_storage ss;
		struct sockaddr_in sin;
#ifdef CONFIG_IPV6
		struct sockaddr_in6 sin6;
#endif /* CONFIG_IPV6 */
	} from;
	socklen_t fromlen;
	int len;
	struct radius_client *client = NULL;
	struct radius_msg *msg = NULL;
	char abuf[50];
	int from_port = 0;

	buf = os_malloc(RADIUS_MAX_MSG_LEN);
	if (buf == NULL) {
		goto fail;
	}

	fromlen = sizeof(from);
	len = recvfrom(sock, buf, RADIUS_MAX_MSG_LEN, 0,
		       (struct sockaddr *) &from.ss, &fromlen);
	if (len < 0) {
		wpa_printf(MSG_INFO, "recvfrom[radius_server]: %s",
			   strerror(errno));
		goto fail;
	}

#ifdef CONFIG_IPV6
	if (data->ipv6) {
		if (inet_ntop(AF_INET6, &from.sin6.sin6_addr, abuf,
			      sizeof(abuf)) == NULL)
			abuf[0] = '\0';
		from_port = ntohs(from.sin6.sin6_port);
		RADIUS_DEBUG("Received %d bytes from %s:%d",
			     len, abuf, from_port);

		client = radius_server_get_client(data,
						  (struct in_addr *)
						  &from.sin6.sin6_addr, 1);
	}
#endif /* CONFIG_IPV6 */

	if (!data->ipv6) {
		os_strlcpy(abuf, inet_ntoa(from.sin.sin_addr), sizeof(abuf));
		from_port = ntohs(from.sin.sin_port);
		RADIUS_DEBUG("Received %d bytes from %s:%d",
			     len, abuf, from_port);

		client = radius_server_get_client(data, &from.sin.sin_addr, 0);
	}

	RADIUS_DUMP("Received data", buf, len);

	if (client == NULL) {
		RADIUS_DEBUG("Unknown client %s - packet ignored", abuf);
		data->counters.invalid_requests++;
		goto fail;
	}

	msg = radius_msg_parse(buf, len);
	if (msg == NULL) {
		RADIUS_DEBUG("Parsing incoming RADIUS frame failed");
		data->counters.malformed_access_requests++;
		client->counters.malformed_access_requests++;
		goto fail;
	}

	os_free(buf);
	buf = NULL;

	if (wpa_debug_level <= MSG_MSGDUMP) {
		radius_msg_dump(msg);
	}

	if (radius_msg_get_hdr(msg)->code == RADIUS_CODE_DISCONNECT_ACK) {
		radius_server_receive_disconnect_resp(data, client, msg, 1);
		return;
	}

	if (radius_msg_get_hdr(msg)->code == RADIUS_CODE_DISCONNECT_NAK) {
		radius_server_receive_disconnect_resp(data, client, msg, 0);
		return;
	}

	if (radius_msg_get_hdr(msg)->code == RADIUS_CODE_COA_ACK) {
		radius_server_receive_coa_resp(data, client, msg, 1);
		return;
	}

	if (radius_msg_get_hdr(msg)->code == RADIUS_CODE_COA_NAK) {
		radius_server_receive_coa_resp(data, client, msg, 0);
		return;
	}

	if (radius_msg_get_hdr(msg)->code != RADIUS_CODE_ACCESS_REQUEST) {
		RADIUS_DEBUG("Unexpected RADIUS code %d",
			     radius_msg_get_hdr(msg)->code);
		data->counters.unknown_types++;
		client->counters.unknown_types++;
		goto fail;
	}

	data->counters.access_requests++;
	client->counters.access_requests++;

	if (radius_msg_verify_msg_auth(msg, (u8 *) client->shared_secret,
				       client->shared_secret_len, NULL)) {
		RADIUS_DEBUG("Invalid Message-Authenticator from %s", abuf);
		data->counters.bad_authenticators++;
		client->counters.bad_authenticators++;
		goto fail;
	}

	if (radius_server_request(data, msg, (struct sockaddr *) &from,
				  fromlen, client, abuf, from_port, NULL) ==
	    -2)
		return; /* msg was stored with the session */

fail:
	radius_msg_free(msg);
	os_free(buf);
}