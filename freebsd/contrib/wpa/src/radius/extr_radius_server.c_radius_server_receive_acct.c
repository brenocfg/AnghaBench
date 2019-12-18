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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  acct_responses; int /*<<< orphan*/  acct_bad_authenticators; int /*<<< orphan*/  acct_requests; int /*<<< orphan*/  unknown_acct_types; int /*<<< orphan*/  malformed_acct_requests; int /*<<< orphan*/  invalid_acct_requests; } ;
struct radius_server_data {int /*<<< orphan*/  acct_sock; TYPE_1__ counters; scalar_t__ ipv6; } ;
struct radius_msg {int dummy; } ;
struct radius_hdr {int /*<<< orphan*/  authenticator; int /*<<< orphan*/  identifier; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int /*<<< orphan*/  acct_responses; int /*<<< orphan*/  acct_bad_authenticators; int /*<<< orphan*/  acct_requests; int /*<<< orphan*/  unknown_acct_types; int /*<<< orphan*/  malformed_acct_requests; } ;
struct radius_client {TYPE_2__ counters; int /*<<< orphan*/  shared_secret_len; scalar_t__ shared_secret; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ MSG_MSGDUMP ; 
 int /*<<< orphan*/  RADIUS_CODE_ACCOUNTING_REQUEST ; 
 int /*<<< orphan*/  RADIUS_CODE_ACCOUNTING_RESPONSE ; 
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
 int /*<<< orphan*/  radius_msg_finish_acct_resp (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 struct wpabuf* radius_msg_get_buf (struct radius_msg*) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radius_msg* radius_msg_parse (int /*<<< orphan*/ *,int) ; 
 scalar_t__ radius_msg_verify_acct_req (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct radius_client* radius_server_get_client (struct radius_server_data*,struct in_addr*,int) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_debug_level ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void radius_server_receive_acct(int sock, void *eloop_ctx,
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
	int len, res;
	struct radius_client *client = NULL;
	struct radius_msg *msg = NULL, *resp = NULL;
	char abuf[50];
	int from_port = 0;
	struct radius_hdr *hdr;
	struct wpabuf *rbuf;

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
		data->counters.invalid_acct_requests++;
		goto fail;
	}

	msg = radius_msg_parse(buf, len);
	if (msg == NULL) {
		RADIUS_DEBUG("Parsing incoming RADIUS frame failed");
		data->counters.malformed_acct_requests++;
		client->counters.malformed_acct_requests++;
		goto fail;
	}

	os_free(buf);
	buf = NULL;

	if (wpa_debug_level <= MSG_MSGDUMP) {
		radius_msg_dump(msg);
	}

	if (radius_msg_get_hdr(msg)->code != RADIUS_CODE_ACCOUNTING_REQUEST) {
		RADIUS_DEBUG("Unexpected RADIUS code %d",
			     radius_msg_get_hdr(msg)->code);
		data->counters.unknown_acct_types++;
		client->counters.unknown_acct_types++;
		goto fail;
	}

	data->counters.acct_requests++;
	client->counters.acct_requests++;

	if (radius_msg_verify_acct_req(msg, (u8 *) client->shared_secret,
				       client->shared_secret_len)) {
		RADIUS_DEBUG("Invalid Authenticator from %s", abuf);
		data->counters.acct_bad_authenticators++;
		client->counters.acct_bad_authenticators++;
		goto fail;
	}

	/* TODO: Write accounting information to a file or database */

	hdr = radius_msg_get_hdr(msg);

	resp = radius_msg_new(RADIUS_CODE_ACCOUNTING_RESPONSE, hdr->identifier);
	if (resp == NULL)
		goto fail;

	radius_msg_finish_acct_resp(resp, (u8 *) client->shared_secret,
				    client->shared_secret_len,
				    hdr->authenticator);

	RADIUS_DEBUG("Reply to %s:%d", abuf, from_port);
	if (wpa_debug_level <= MSG_MSGDUMP) {
		radius_msg_dump(resp);
	}
	rbuf = radius_msg_get_buf(resp);
	data->counters.acct_responses++;
	client->counters.acct_responses++;
	res = sendto(data->acct_sock, wpabuf_head(rbuf), wpabuf_len(rbuf), 0,
		     (struct sockaddr *) &from.ss, fromlen);
	if (res < 0) {
		wpa_printf(MSG_INFO, "sendto[RADIUS SRV]: %s",
			   strerror(errno));
	}

fail:
	radius_msg_free(resp);
	radius_msg_free(msg);
	os_free(buf);
}