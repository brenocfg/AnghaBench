#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct sta_info {struct wpabuf* hlp_dhcp_discover; } ;
struct TYPE_16__ {scalar_t__ s_addr; } ;
struct sockaddr_in {void* sin_port; TYPE_8__ sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostapd_data {int dhcp_sock; TYPE_7__* conf; } ;
struct dhcp_data {int op; scalar_t__ relay_ip; int /*<<< orphan*/  xid; int /*<<< orphan*/  hops; int /*<<< orphan*/  hlen; int /*<<< orphan*/  htype; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_12__ {scalar_t__ s_addr; } ;
struct TYPE_13__ {TYPE_4__ v4; } ;
struct TYPE_14__ {scalar_t__ af; TYPE_5__ u; } ;
struct TYPE_9__ {scalar_t__ s_addr; } ;
struct TYPE_10__ {TYPE_1__ v4; } ;
struct TYPE_11__ {scalar_t__ af; TYPE_2__ u; } ;
struct TYPE_15__ {scalar_t__ dhcp_rapid_commit_proxy; scalar_t__ dhcp_server_port; TYPE_6__ dhcp_server; TYPE_3__ own_ip_addr; scalar_t__ dhcp_relay_port; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ DHCPDISCOVER ; 
 scalar_t__ DHCP_MAGIC ; 
 scalar_t__ const DHCP_OPT_END ; 
#define  DHCP_OPT_MSG_TYPE 129 
 scalar_t__ DHCP_OPT_PAD ; 
#define  DHCP_OPT_RAPID_COMMIT 128 
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ WPA_GET_BE32 (scalar_t__ const*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ eloop_register_sock (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hostapd_data*) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fils_dhcp_handler ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_8__) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (void*) ; 
 int /*<<< orphan*/  os_memcpy (struct dhcp_data*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendto (int,struct dhcp_data*,size_t,int /*<<< orphan*/ ,struct sockaddr const*,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct dhcp_data* wpabuf_put (struct wpabuf*,size_t) ; 

__attribute__((used)) static int fils_process_hlp_dhcp(struct hostapd_data *hapd,
				 struct sta_info *sta,
				 const u8 *msg, size_t len)
{
	const struct dhcp_data *dhcp;
	struct wpabuf *dhcp_buf;
	struct dhcp_data *dhcp_msg;
	u8 msgtype = 0;
	int rapid_commit = 0;
	const u8 *pos = msg, *end;
	struct sockaddr_in addr;
	ssize_t res;

	if (len < sizeof(*dhcp))
		return 0;
	dhcp = (const struct dhcp_data *) pos;
	end = pos + len;
	wpa_printf(MSG_DEBUG,
		   "FILS: HLP request DHCP: op=%u htype=%u hlen=%u hops=%u xid=0x%x",
		   dhcp->op, dhcp->htype, dhcp->hlen, dhcp->hops,
		   ntohl(dhcp->xid));
	pos += sizeof(*dhcp);
	if (dhcp->op != 1)
		return 0; /* Not a BOOTREQUEST */

	if (end - pos < 4)
		return 0;
	if (WPA_GET_BE32(pos) != DHCP_MAGIC) {
		wpa_printf(MSG_DEBUG, "FILS: HLP - no DHCP magic");
		return 0;
	}
	pos += 4;

	wpa_hexdump(MSG_DEBUG, "FILS: HLP - DHCP options", pos, end - pos);
	while (pos < end && *pos != DHCP_OPT_END) {
		u8 opt, olen;

		opt = *pos++;
		if (opt == DHCP_OPT_PAD)
			continue;
		if (pos >= end)
			break;
		olen = *pos++;
		if (olen > end - pos)
			break;

		switch (opt) {
		case DHCP_OPT_MSG_TYPE:
			if (olen > 0)
				msgtype = pos[0];
			break;
		case DHCP_OPT_RAPID_COMMIT:
			rapid_commit = 1;
			break;
		}
		pos += olen;
	}

	wpa_printf(MSG_DEBUG, "FILS: HLP - DHCP message type %u", msgtype);
	if (msgtype != DHCPDISCOVER)
		return 0;

	if (hapd->conf->dhcp_server.af != AF_INET ||
	    hapd->conf->dhcp_server.u.v4.s_addr == 0) {
		wpa_printf(MSG_DEBUG,
			   "FILS: HLP - no DHCPv4 server configured - drop request");
		return 0;
	}

	if (hapd->conf->own_ip_addr.af != AF_INET ||
	    hapd->conf->own_ip_addr.u.v4.s_addr == 0) {
		wpa_printf(MSG_DEBUG,
			   "FILS: HLP - no IPv4 own_ip_addr configured - drop request");
		return 0;
	}

	if (hapd->dhcp_sock < 0) {
		int s;

		s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s < 0) {
			wpa_printf(MSG_ERROR,
				   "FILS: Failed to open DHCP socket: %s",
				   strerror(errno));
			return 0;
		}

		if (hapd->conf->dhcp_relay_port) {
			os_memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr =
				hapd->conf->own_ip_addr.u.v4.s_addr;
			addr.sin_port = htons(hapd->conf->dhcp_relay_port);
			if (bind(s, (struct sockaddr *) &addr, sizeof(addr))) {
				wpa_printf(MSG_ERROR,
					   "FILS: Failed to bind DHCP socket: %s",
					   strerror(errno));
				close(s);
				return 0;
			}
		}
		if (eloop_register_sock(s, EVENT_TYPE_READ,
					fils_dhcp_handler, NULL, hapd)) {
			close(s);
			return 0;
		}

		hapd->dhcp_sock = s;
	}

	dhcp_buf = wpabuf_alloc(len);
	if (!dhcp_buf)
		return 0;
	dhcp_msg = wpabuf_put(dhcp_buf, len);
	os_memcpy(dhcp_msg, msg, len);
	dhcp_msg->relay_ip = hapd->conf->own_ip_addr.u.v4.s_addr;
	os_memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = hapd->conf->dhcp_server.u.v4.s_addr;
	addr.sin_port = htons(hapd->conf->dhcp_server_port);
	res = sendto(hapd->dhcp_sock, dhcp_msg, len, 0,
		     (const struct sockaddr *) &addr, sizeof(addr));
	if (res < 0) {
		wpa_printf(MSG_ERROR, "FILS: DHCP sendto failed: %s",
			   strerror(errno));
		wpabuf_free(dhcp_buf);
		/* Close the socket to try to recover from error */
		eloop_unregister_read_sock(hapd->dhcp_sock);
		close(hapd->dhcp_sock);
		hapd->dhcp_sock = -1;
		return 0;
	}

	wpa_printf(MSG_DEBUG,
		   "FILS: HLP relayed DHCP request to server %s:%d (rapid_commit=%d)",
		   inet_ntoa(addr.sin_addr), ntohs(addr.sin_port),
		   rapid_commit);
	if (hapd->conf->dhcp_rapid_commit_proxy && rapid_commit) {
		/* Store a copy of the DHCPDISCOVER for rapid commit proxying
		 * purposes if the server does not support the rapid commit
		 * option. */
		wpa_printf(MSG_DEBUG,
			   "FILS: Store DHCPDISCOVER for rapid commit proxy");
		wpabuf_free(sta->hlp_dhcp_discover);
		sta->hlp_dhcp_discover = dhcp_buf;
	} else {
		wpabuf_free(dhcp_buf);
	}

	return 1;
}