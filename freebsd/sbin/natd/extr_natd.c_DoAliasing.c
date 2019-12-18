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
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct ip {int ip_p; int /*<<< orphan*/  ip_len; } ;
typedef  int socklen_t ;
struct TYPE_4__ {char* name; int aliasOverhead; int ifMTU; scalar_t__ logDropped; scalar_t__ dropIgnoredIncoming; scalar_t__ assignAliasAddr; int /*<<< orphan*/  ifName; } ;

/* Variables and functions */
 int DONT_KNOW ; 
 scalar_t__ EACCES ; 
 int EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EMSGSIZE ; 
 scalar_t__ INADDR_ANY ; 
 int INPUT ; 
#define  IPPROTO_ICMP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IP_MAXPACKET ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int LibAliasIn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LibAliasOut (int /*<<< orphan*/ ,char*,int) ; 
 int OUTPUT ; 
 int PKT_ALIAS_IGNORED ; 
 int /*<<< orphan*/  PrintPacket (struct ip*) ; 
 int /*<<< orphan*/  SendNeedFragIcmp (int /*<<< orphan*/ ,struct ip*,int) ; 
 int SetAliasAddressFromIfName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SyslogPacket (struct ip*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Warn (char*) ; 
 scalar_t__ background ; 
 scalar_t__ dynamicMode ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  icmpSock ; 
 scalar_t__ logIpfwDenied ; 
 TYPE_2__* mip ; 
 int /*<<< orphan*/  mla ; 
 int ninstance ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void DoAliasing (int fd, int direction)
{
	int			bytes;
	int			origBytes;
	char			buf[IP_MAXPACKET];
	struct sockaddr_in	addr;
	int			wrote;
	int			status;
	socklen_t		addrSize;
	struct ip*		ip;
	char			msgBuf[80];
	int			rval;

	if (mip->assignAliasAddr) {
		do {
			rval = SetAliasAddressFromIfName (mip->ifName);
			if (background == 0 || dynamicMode == 0)
				break;
			if (rval == EAGAIN)
				sleep(1);
		} while (rval == EAGAIN);
		if (rval != 0)
			exit(1);
		mip->assignAliasAddr = 0;
	}
/*
 * Get packet from socket.
 */
	addrSize  = sizeof addr;
	origBytes = recvfrom (fd,
			      buf,
			      sizeof buf,
			      0,
			      (struct sockaddr*) &addr,
			      &addrSize);

	if (origBytes == -1) {

		if (errno != EINTR)
			Warn ("read from divert socket failed");

		return;
	}
/*
 * This is an IP packet.
 */
	ip = (struct ip*) buf;
	if (direction == DONT_KNOW) {
		if (addr.sin_addr.s_addr == INADDR_ANY)
			direction = OUTPUT;
		else
			direction = INPUT;
	}

	if (verbose) {
/*
 * Print packet direction and protocol type.
 */
		printf (direction == OUTPUT ? "Out " : "In  ");
		if (ninstance > 1)
			printf ("{%s}", mip->name);

		switch (ip->ip_p) {
		case IPPROTO_TCP:
			printf ("[TCP]  ");
			break;

		case IPPROTO_UDP:
			printf ("[UDP]  ");
			break;

		case IPPROTO_ICMP:
			printf ("[ICMP] ");
			break;

		default:
			printf ("[%d]    ", ip->ip_p);
			break;
		}
/*
 * Print addresses.
 */
		PrintPacket (ip);
	}

	if (direction == OUTPUT) {
/*
 * Outgoing packets. Do aliasing.
 */
		LibAliasOut (mla, buf, IP_MAXPACKET);
	}
	else {

/*
 * Do aliasing.
 */	
		status = LibAliasIn (mla, buf, IP_MAXPACKET);
		if (status == PKT_ALIAS_IGNORED &&
		    mip->dropIgnoredIncoming) {

			if (verbose)
				printf (" dropped.\n");

			if (mip->logDropped)
				SyslogPacket (ip, LOG_WARNING, "denied");

			return;
		}
	}
/*
 * Length might have changed during aliasing.
 */
	bytes = ntohs (ip->ip_len);
/*
 * Update alias overhead size for outgoing packets.
 */
	if (direction == OUTPUT &&
	    bytes - origBytes > mip->aliasOverhead)
		mip->aliasOverhead = bytes - origBytes;

	if (verbose) {
		
/*
 * Print addresses after aliasing.
 */
		printf (" aliased to\n");
		printf ("           ");
		PrintPacket (ip);
		printf ("\n");
	}

/*
 * Put packet back for processing.
 */
	wrote = sendto (fd, 
		        buf,
	    		bytes,
	    		0,
	    		(struct sockaddr*) &addr,
	    		sizeof addr);
	
	if (wrote != bytes) {

		if (errno == EMSGSIZE) {

			if (direction == OUTPUT &&
			    mip->ifMTU != -1)
				SendNeedFragIcmp (icmpSock,
						  (struct ip*) buf,
						  mip->ifMTU - mip->aliasOverhead);
		}
		else if (errno == EACCES && logIpfwDenied) {

			sprintf (msgBuf, "failed to write packet back");
			Warn (msgBuf);
		}
	}
}