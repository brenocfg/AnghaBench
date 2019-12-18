#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int sin_family; int sin6_family; void* sin6_port; int /*<<< orphan*/  sin6_addr; void* sin_port; TYPE_6__ sin_addr; } ;
struct sockaddr_in {int sin_family; int sin6_family; void* sin6_port; int /*<<< orphan*/  sin6_addr; void* sin_port; TYPE_6__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct radius_msg_list {scalar_t__ msg_type; int attempts; int next_wait; scalar_t__ first_try; scalar_t__ next_try; struct radius_msg_list* next; } ;
struct radius_client_data {int auth_sock; int acct_sock; struct radius_msg_list* msgs; int /*<<< orphan*/  ctx; struct hostapd_radius_servers* conf; } ;
struct in6_addr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  v6; TYPE_3__ v4; } ;
struct TYPE_12__ {int af; TYPE_4__ u; } ;
struct hostapd_radius_servers {TYPE_5__ client_addr; scalar_t__ force_client_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  v6; TYPE_1__ v4; } ;
struct TYPE_14__ {int af; TYPE_2__ u; } ;
struct hostapd_radius_server {scalar_t__ shared_secret_len; TYPE_7__ addr; int /*<<< orphan*/  port; int /*<<< orphan*/  shared_secret; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  serv6 ;
typedef  int /*<<< orphan*/  serv ;
typedef  int /*<<< orphan*/  disconnect_addr ;
typedef  int /*<<< orphan*/  claddr6 ;
typedef  int /*<<< orphan*/  claddr ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int AF_UNSPEC ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ RADIUS_ACCT ; 
 scalar_t__ RADIUS_AUTH ; 
 int RADIUS_CLIENT_FIRST_WAIT ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct radius_client_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radius_client_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  hostapd_ip_txt (TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_6__) ; 
 int /*<<< orphan*/  inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntohs (void*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_client_flush (struct radius_client_data*,int) ; 
 int /*<<< orphan*/  radius_client_timer ; 
 int /*<<< orphan*/  radius_client_update_acct_msgs (struct radius_client_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int
radius_change_server(struct radius_client_data *radius,
		     struct hostapd_radius_server *nserv,
		     struct hostapd_radius_server *oserv,
		     int sock, int sock6, int auth)
{
	struct sockaddr_in serv, claddr;
#ifdef CONFIG_IPV6
	struct sockaddr_in6 serv6, claddr6;
#endif /* CONFIG_IPV6 */
	struct sockaddr *addr, *cl_addr;
	socklen_t addrlen, claddrlen;
	char abuf[50];
	int sel_sock;
	struct radius_msg_list *entry;
	struct hostapd_radius_servers *conf = radius->conf;
	struct sockaddr_in disconnect_addr = {
		.sin_family = AF_UNSPEC,
	};

	hostapd_logger(radius->ctx, NULL, HOSTAPD_MODULE_RADIUS,
		       HOSTAPD_LEVEL_INFO,
		       "%s server %s:%d",
		       auth ? "Authentication" : "Accounting",
		       hostapd_ip_txt(&nserv->addr, abuf, sizeof(abuf)),
		       nserv->port);

	if (oserv && oserv == nserv) {
		/* Reconnect to same server, flush */
		if (auth)
			radius_client_flush(radius, 1);
	}

	if (oserv && oserv != nserv &&
	    (nserv->shared_secret_len != oserv->shared_secret_len ||
	     os_memcmp(nserv->shared_secret, oserv->shared_secret,
		       nserv->shared_secret_len) != 0)) {
		/* Pending RADIUS packets used different shared secret, so
		 * they need to be modified. Update accounting message
		 * authenticators here. Authentication messages are removed
		 * since they would require more changes and the new RADIUS
		 * server may not be prepared to receive them anyway due to
		 * missing state information. Client will likely retry
		 * authentication, so this should not be an issue. */
		if (auth)
			radius_client_flush(radius, 1);
		else {
			radius_client_update_acct_msgs(
				radius, nserv->shared_secret,
				nserv->shared_secret_len);
		}
	}

	/* Reset retry counters */
	for (entry = radius->msgs; oserv && entry; entry = entry->next) {
		if ((auth && entry->msg_type != RADIUS_AUTH) ||
		    (!auth && entry->msg_type != RADIUS_ACCT))
			continue;
		entry->next_try = entry->first_try + RADIUS_CLIENT_FIRST_WAIT;
		entry->attempts = 1;
		entry->next_wait = RADIUS_CLIENT_FIRST_WAIT * 2;
	}

	if (radius->msgs) {
		eloop_cancel_timeout(radius_client_timer, radius, NULL);
		eloop_register_timeout(RADIUS_CLIENT_FIRST_WAIT, 0,
				       radius_client_timer, radius, NULL);
	}

	switch (nserv->addr.af) {
	case AF_INET:
		os_memset(&serv, 0, sizeof(serv));
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = nserv->addr.u.v4.s_addr;
		serv.sin_port = htons(nserv->port);
		addr = (struct sockaddr *) &serv;
		addrlen = sizeof(serv);
		sel_sock = sock;
		break;
#ifdef CONFIG_IPV6
	case AF_INET6:
		os_memset(&serv6, 0, sizeof(serv6));
		serv6.sin6_family = AF_INET6;
		os_memcpy(&serv6.sin6_addr, &nserv->addr.u.v6,
			  sizeof(struct in6_addr));
		serv6.sin6_port = htons(nserv->port);
		addr = (struct sockaddr *) &serv6;
		addrlen = sizeof(serv6);
		sel_sock = sock6;
		break;
#endif /* CONFIG_IPV6 */
	default:
		return -1;
	}

	if (sel_sock < 0) {
		wpa_printf(MSG_INFO,
			   "RADIUS: No server socket available (af=%d sock=%d sock6=%d auth=%d",
			   nserv->addr.af, sock, sock6, auth);
		return -1;
	}

	if (conf->force_client_addr) {
		switch (conf->client_addr.af) {
		case AF_INET:
			os_memset(&claddr, 0, sizeof(claddr));
			claddr.sin_family = AF_INET;
			claddr.sin_addr.s_addr = conf->client_addr.u.v4.s_addr;
			claddr.sin_port = htons(0);
			cl_addr = (struct sockaddr *) &claddr;
			claddrlen = sizeof(claddr);
			break;
#ifdef CONFIG_IPV6
		case AF_INET6:
			os_memset(&claddr6, 0, sizeof(claddr6));
			claddr6.sin6_family = AF_INET6;
			os_memcpy(&claddr6.sin6_addr, &conf->client_addr.u.v6,
				  sizeof(struct in6_addr));
			claddr6.sin6_port = htons(0);
			cl_addr = (struct sockaddr *) &claddr6;
			claddrlen = sizeof(claddr6);
			break;
#endif /* CONFIG_IPV6 */
		default:
			return -1;
		}

		if (bind(sel_sock, cl_addr, claddrlen) < 0) {
			wpa_printf(MSG_INFO, "bind[radius]: %s",
				   strerror(errno));
			return -1;
		}
	}

	/* Force a reconnect by disconnecting the socket first */
	if (connect(sel_sock, (struct sockaddr *) &disconnect_addr,
		    sizeof(disconnect_addr)) < 0)
		wpa_printf(MSG_INFO, "disconnect[radius]: %s", strerror(errno));

	if (connect(sel_sock, addr, addrlen) < 0) {
		wpa_printf(MSG_INFO, "connect[radius]: %s", strerror(errno));
		return -1;
	}

#ifndef CONFIG_NATIVE_WINDOWS
	switch (nserv->addr.af) {
	case AF_INET:
		claddrlen = sizeof(claddr);
		if (getsockname(sel_sock, (struct sockaddr *) &claddr,
				&claddrlen) == 0) {
			wpa_printf(MSG_DEBUG, "RADIUS local address: %s:%u",
				   inet_ntoa(claddr.sin_addr),
				   ntohs(claddr.sin_port));
		}
		break;
#ifdef CONFIG_IPV6
	case AF_INET6: {
		claddrlen = sizeof(claddr6);
		if (getsockname(sel_sock, (struct sockaddr *) &claddr6,
				&claddrlen) == 0) {
			wpa_printf(MSG_DEBUG, "RADIUS local address: %s:%u",
				   inet_ntop(AF_INET6, &claddr6.sin6_addr,
					     abuf, sizeof(abuf)),
				   ntohs(claddr6.sin6_port));
		}
		break;
	}
#endif /* CONFIG_IPV6 */
	}
#endif /* CONFIG_NATIVE_WINDOWS */

	if (auth)
		radius->auth_sock = sel_sock;
	else
		radius->acct_sock = sel_sock;

	return 0;
}