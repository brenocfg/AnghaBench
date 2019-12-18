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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_char ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct my_pmtu {int /*<<< orphan*/  ipm_nextmtu; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_dst; } ;
struct TYPE_4__ {int ip_hl; scalar_t__ ip_p; } ;
struct icmp {scalar_t__ icmp_type; scalar_t__ icmp_code; TYPE_2__ icmp_ip; int /*<<< orphan*/  icmp_void; int /*<<< orphan*/  icmp_nextmtu; } ;
struct TYPE_3__ {scalar_t__ num; scalar_t__ (* check ) (scalar_t__*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ICMP_ECHOREPLY ; 
 int ICMP_MINLEN ; 
 scalar_t__ ICMP_TIMXCEED ; 
 scalar_t__ ICMP_TIMXCEED_INTRANS ; 
 scalar_t__ ICMP_UNREACH ; 
 scalar_t__ ICMP_UNREACH_NEEDFRAG ; 
 scalar_t__ IPPROTO_ICMP ; 
 int /*<<< orphan*/  Printf (char*,int,scalar_t__,...) ; 
 TYPE_2__* hip ; 
 int hiplen ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ pmtu ; 
 int /*<<< orphan*/  pr_type (scalar_t__) ; 
 TYPE_1__* proto ; 
 scalar_t__ stub1 (scalar_t__*,scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__*,scalar_t__) ; 
 scalar_t__ verbose ; 

int
packet_ok(register u_char *buf, int cc, register struct sockaddr_in *from,
    register int seq)
{
	register struct icmp *icp;
	register u_char type, code;
	register int hlen;
#ifndef ARCHAIC
	register struct ip *ip;

	ip = (struct ip *) buf;
	hlen = ip->ip_hl << 2;
	if (cc < hlen + ICMP_MINLEN) {
		if (verbose)
			Printf("packet too short (%d bytes) from %s\n", cc,
				inet_ntoa(from->sin_addr));
		return (0);
	}
	cc -= hlen;
	icp = (struct icmp *)(buf + hlen);
#else
	icp = (struct icmp *)buf;
#endif
	type = icp->icmp_type;
	code = icp->icmp_code;
	/* Path MTU Discovery (RFC1191) */
	if (code != ICMP_UNREACH_NEEDFRAG)
		pmtu = 0;
	else {
#ifdef HAVE_ICMP_NEXTMTU
		pmtu = ntohs(icp->icmp_nextmtu);
#else
		pmtu = ntohs(((struct my_pmtu *)&icp->icmp_void)->ipm_nextmtu);
#endif
	}
	if (type == ICMP_ECHOREPLY
	    && proto->num == IPPROTO_ICMP
	    && (*proto->check)((u_char *)icp, (u_char)seq))
		return -2;
	if ((type == ICMP_TIMXCEED && code == ICMP_TIMXCEED_INTRANS) ||
	    type == ICMP_UNREACH) {
		u_char *inner;

		hip = &icp->icmp_ip;
		hiplen = ((u_char *)icp + cc) - (u_char *)hip;
		hlen = hip->ip_hl << 2;
		inner = (u_char *)((u_char *)hip + hlen);
		if (hlen + 16 <= cc
		    && hip->ip_p == proto->num
		    && (*proto->check)(inner, (u_char)seq))
			return (type == ICMP_TIMXCEED ? -1 : code + 1);
	}
#ifndef ARCHAIC
	if (verbose) {
		register int i;
		u_int32_t *lp = (u_int32_t *)&icp->icmp_ip;

		Printf("\n%d bytes from %s to ", cc, inet_ntoa(from->sin_addr));
		Printf("%s: icmp type %d (%s) code %d\n",
		    inet_ntoa(ip->ip_dst), type, pr_type(type), icp->icmp_code);
		for (i = 4; i <= cc - ICMP_MINLEN; i += sizeof(*lp))
			Printf("%2d: %8.8x\n", i, ntohl(*lp++));
	}
#endif
	return(0);
}