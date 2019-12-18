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
struct upnp_wps_device_sm {int /*<<< orphan*/  ssdp_sd; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int MULTICAST_MAX_READ ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isgraph (char) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 scalar_t__ os_strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  ssdp_parse_msearch (struct upnp_wps_device_sm*,struct sockaddr_in*,char*) ; 
 scalar_t__ str_starts (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ssdp_listener_handler(int sd, void *eloop_ctx, void *sock_ctx)
{
	struct upnp_wps_device_sm *sm = sock_ctx;
	struct sockaddr_in addr; /* client address */
	socklen_t addr_len;
	int nread;
	char buf[MULTICAST_MAX_READ], *pos;

	addr_len = sizeof(addr);
	nread = recvfrom(sm->ssdp_sd, buf, sizeof(buf) - 1, 0,
			 (struct sockaddr *) &addr, &addr_len);
	if (nread <= 0)
		return;
	buf[nread] = '\0'; /* need null termination for algorithm */

	if (str_starts(buf, "NOTIFY ")) {
		/*
		 * Silently ignore NOTIFYs to avoid filling debug log with
		 * unwanted messages.
		 */
		return;
	}

	pos = os_strchr(buf, '\n');
	if (pos)
		*pos = '\0';
	wpa_printf(MSG_MSGDUMP, "WPS UPnP: Received SSDP packet from %s:%d: "
		   "%s", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buf);
	if (pos)
		*pos = '\n';

	/* Parse first line */
	if (os_strncasecmp(buf, "M-SEARCH", os_strlen("M-SEARCH")) == 0 &&
	    !isgraph(buf[strlen("M-SEARCH")])) {
		ssdp_parse_msearch(sm, &addr, buf);
		return;
	}

	/* Ignore anything else */
}