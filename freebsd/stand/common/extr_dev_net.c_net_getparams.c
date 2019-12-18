#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* n_long ;
struct TYPE_6__ {scalar_t__ s_addr; } ;

/* Variables and functions */
 int EIO ; 
 void* INADDR_NONE ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  bootp (int) ; 
 scalar_t__ bp_getfile (int,char*,TYPE_1__*,char*) ; 
 scalar_t__ bp_whoami (int) ; 
 scalar_t__ debug ; 
 TYPE_1__ gateip ; 
 char* hostname ; 
 char* inet_ntoa (TYPE_1__) ; 
 char* intoa (void*) ; 
 void* ip_convertaddr (char*) ; 
 TYPE_1__ myip ; 
 void* net_parse_rootpath () ; 
 void* netmask ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ rarp_getipaddress (int) ; 
 TYPE_1__ rootip ; 
 char* rootpath ; 
 scalar_t__ try_bootp ; 

__attribute__((used)) static int
net_getparams(int sock)
{
	char buf[MAXHOSTNAMELEN];
	n_long rootaddr, smask;

#ifdef	SUPPORT_BOOTP
	/*
	 * Try to get boot info using BOOTP.  If we succeed, then
	 * the server IP address, gateway, and root path will all
	 * be initialized.  If any remain uninitialized, we will
	 * use RARP and RPC/bootparam (the Sun way) to get them.
	 */
	if (try_bootp)
		bootp(sock);
	if (myip.s_addr != 0)
		goto exit;
#ifdef	NETIF_DEBUG
	if (debug)
		printf("net_open: BOOTP failed, trying RARP/RPC...\n");
#endif
#endif

	/*
	 * Use RARP to get our IP address.  This also sets our
	 * netmask to the "natural" default for our address.
	 */
	if (rarp_getipaddress(sock)) {
		printf("net_open: RARP failed\n");
		return (EIO);
	}
	printf("net_open: client addr: %s\n", inet_ntoa(myip));

	/* Get our hostname, server IP address, gateway. */
	if (bp_whoami(sock)) {
		printf("net_open: bootparam/whoami RPC failed\n");
		return (EIO);
	}
#ifdef	NETIF_DEBUG
	if (debug)
		printf("net_open: client name: %s\n", hostname);
#endif

	/*
	 * Ignore the gateway from whoami (unreliable).
	 * Use the "gateway" parameter instead.
	 */
	smask = 0;
	gateip.s_addr = 0;
	if (bp_getfile(sock, "gateway", &gateip, buf) == 0) {
		/* Got it!  Parse the netmask. */
		smask = ip_convertaddr(buf);
	}
	if (smask) {
		netmask = smask;
#ifdef	NETIF_DEBUG
		if (debug)
			printf("net_open: subnet mask: %s\n", intoa(netmask));
#endif
	}
#ifdef	NETIF_DEBUG
	if (gateip.s_addr && debug)
		printf("net_open: net gateway: %s\n", inet_ntoa(gateip));
#endif

	/* Get the root server and pathname. */
	if (bp_getfile(sock, "root", &rootip, rootpath)) {
		printf("net_open: bootparam/getfile RPC failed\n");
		return (EIO);
	}
exit:
	if ((rootaddr = net_parse_rootpath()) != INADDR_NONE)
		rootip.s_addr = rootaddr;

#ifdef	NETIF_DEBUG
	if (debug) {
		printf("net_open: server addr: %s\n", inet_ntoa(rootip));
		printf("net_open: server path: %s\n", rootpath);
	}
#endif

	return (0);
}