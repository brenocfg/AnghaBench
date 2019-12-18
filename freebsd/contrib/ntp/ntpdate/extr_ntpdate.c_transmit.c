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
typedef  int /*<<< orphan*/  u_int32 ;
struct server {scalar_t__ filter_nextpt; scalar_t__ xmtcnt; scalar_t__ event_time; int /*<<< orphan*/  srcadr; int /*<<< orphan*/  xmt; } ;
struct pkt {int /*<<< orphan*/  xmt; void** exten; int /*<<< orphan*/  rec; int /*<<< orphan*/  org; int /*<<< orphan*/  reftime; void* refid; void* rootdisp; void* rootdelay; int /*<<< orphan*/  precision; int /*<<< orphan*/  ppoll; int /*<<< orphan*/  stratum; int /*<<< orphan*/  li_vn_mode; } ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  HTONL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEAP_NOTINSYNC ; 
 size_t LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  L_ADDUF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L_CLR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MODE_CLIENT ; 
 int /*<<< orphan*/  NTPDATE_DISP ; 
 int /*<<< orphan*/  NTPDATE_DISTANCE ; 
 int /*<<< orphan*/  NTPDATE_PRECISION ; 
 int /*<<< orphan*/  NTPDATE_REFID ; 
 int /*<<< orphan*/  NTP_MINPOLL ; 
 int /*<<< orphan*/  PKT_LI_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRATUM_TO_PKT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRATUM_UNSPEC ; 
 size_t authencrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  complete_servers ; 
 scalar_t__ current_time ; 
 int debug ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sendpkt (int /*<<< orphan*/ *,struct pkt*,size_t) ; 
 int /*<<< orphan*/  server_data (struct server*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_authdelay ; 
 scalar_t__ sys_authenticate ; 
 int /*<<< orphan*/  sys_authkey ; 
 int sys_samples ; 
 scalar_t__ sys_timeout ; 
 int /*<<< orphan*/  sys_version ; 

__attribute__((used)) static void
transmit(
	register struct server *server
	)
{
	struct pkt xpkt;

	if (server->filter_nextpt < server->xmtcnt) {
		l_fp ts;
		/*
		 * Last message to this server timed out.  Shift
		 * zeros into the filter.
		 */
		L_CLR(&ts);
		server_data(server, 0, &ts, 0);
	}

	if ((int)server->filter_nextpt >= sys_samples) {
		/*
		 * Got all the data we need.  Mark this guy
		 * completed and return.
		 */
		server->event_time = 0;
		complete_servers++;
		return;
	}

	if (debug)
		printf("transmit(%s)\n", stoa(&server->srcadr));

	/*
	 * If we're here, send another message to the server.  Fill in
	 * the packet and let 'er rip.
	 */
	xpkt.li_vn_mode = PKT_LI_VN_MODE(LEAP_NOTINSYNC,
					 sys_version, MODE_CLIENT);
	xpkt.stratum = STRATUM_TO_PKT(STRATUM_UNSPEC);
	xpkt.ppoll = NTP_MINPOLL;
	xpkt.precision = NTPDATE_PRECISION;
	xpkt.rootdelay = htonl(NTPDATE_DISTANCE);
	xpkt.rootdisp = htonl(NTPDATE_DISP);
	xpkt.refid = htonl(NTPDATE_REFID);
	L_CLR(&xpkt.reftime);
	L_CLR(&xpkt.org);
	L_CLR(&xpkt.rec);

	/*
	 * Determine whether to authenticate or not.	If so,
	 * fill in the extended part of the packet and do it.
	 * If not, just timestamp it and send it away.
	 */
	if (sys_authenticate) {
		size_t len;

		xpkt.exten[0] = htonl(sys_authkey);
		get_systime(&server->xmt);
		L_ADDUF(&server->xmt, sys_authdelay);
		HTONL_FP(&server->xmt, &xpkt.xmt);
		len = authencrypt(sys_authkey, (u_int32 *)&xpkt, LEN_PKT_NOMAC);
		sendpkt(&server->srcadr, &xpkt, (int)(LEN_PKT_NOMAC + len));

		if (debug > 1)
			printf("transmit auth to %s\n",
			   stoa(&server->srcadr));
	} else {
		get_systime(&(server->xmt));
		HTONL_FP(&server->xmt, &xpkt.xmt);
		sendpkt(&server->srcadr, &xpkt, LEN_PKT_NOMAC);

		if (debug > 1)
			printf("transmit to %s\n", stoa(&server->srcadr));
	}

	/*
	 * Update the server timeout and transmit count
	 */
	server->event_time = current_time + sys_timeout;
	server->xmtcnt++;
}