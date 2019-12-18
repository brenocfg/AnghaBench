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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct ip {int ip_hl; int ip_p; TYPE_1__ ip_dst; TYPE_1__ ip_src; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/  ip_ttl; int /*<<< orphan*/  ip_len; int /*<<< orphan*/  ip_v; } ;
struct iodesc {TYPE_1__ destip; TYPE_1__ myip; int /*<<< orphan*/  destport; int /*<<< orphan*/  myport; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 scalar_t__ INADDR_BROADCAST ; 
 int /*<<< orphan*/  IPDEFTTL ; 
 int /*<<< orphan*/  IPVERSION ; 
 scalar_t__ SAMENET (TYPE_1__,TYPE_1__,scalar_t__) ; 
 int /*<<< orphan*/ * arpwhohas (struct iodesc*,TYPE_1__) ; 
 int /*<<< orphan*/  bzero (struct ip*,int) ; 
 scalar_t__ debug ; 
 TYPE_1__ gateip ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  in_cksum (struct ip*,int) ; 
 char* inet_ntoa (TYPE_1__) ; 
 scalar_t__ netmask ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sendether (struct iodesc*,struct ip*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ssize_t
sendip(struct iodesc *d, void *pkt, size_t len, uint8_t proto)
{
	ssize_t cc;
	struct ip *ip;
	u_char *ea;

#ifdef NET_DEBUG
	if (debug) {
		printf("sendip: proto: %x d=%p called.\n", proto, (void *)d);
		if (d) {
			printf("saddr: %s:%d",
			    inet_ntoa(d->myip), ntohs(d->myport));
			printf(" daddr: %s:%d\n",
			    inet_ntoa(d->destip), ntohs(d->destport));
		}
	}
#endif

	ip = (struct ip *)pkt - 1;
	len += sizeof(*ip);

	bzero(ip, sizeof(*ip));

	ip->ip_v = IPVERSION;			/* half-char */
	ip->ip_hl = sizeof(*ip) >> 2;		/* half-char */
	ip->ip_len = htons(len);
	ip->ip_p = proto;			/* char */
	ip->ip_ttl = IPDEFTTL;			/* char */
	ip->ip_src = d->myip;
	ip->ip_dst = d->destip;
	ip->ip_sum = in_cksum(ip, sizeof(*ip));	 /* short, but special */

	if (ip->ip_dst.s_addr == INADDR_BROADCAST || ip->ip_src.s_addr == 0 ||
	    netmask == 0 || SAMENET(ip->ip_src, ip->ip_dst, netmask))
		ea = arpwhohas(d, ip->ip_dst);
	else
		ea = arpwhohas(d, gateip);

	cc = sendether(d, ip, len, ea, ETHERTYPE_IP);
	if (cc == -1)
		return (-1);
	if (cc != len)
		panic("sendip: bad write (%zd != %zd)", cc, len);
	return (cc - sizeof(*ip));
}