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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_hl; int ip_v; int ip_tos; int ip_ttl; int ip_p; TYPE_2__ ip_dst; TYPE_1__ ip_src; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/  ip_off; int /*<<< orphan*/  ip_id; int /*<<< orphan*/  ip_len; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ *,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
pr_iph(struct ip *ip)
{
	struct in_addr ina;
	u_char *cp;
	int hlen;

	hlen = ip->ip_hl << 2;
	cp = (u_char *)ip + 20;		/* point to options */

	(void)printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst\n");
	(void)printf(" %1x  %1x  %02x %04x %04x",
	    ip->ip_v, ip->ip_hl, ip->ip_tos, ntohs(ip->ip_len),
	    ntohs(ip->ip_id));
	(void)printf("   %1lx %04lx",
	    (u_long) (ntohl(ip->ip_off) & 0xe000) >> 13,
	    (u_long) ntohl(ip->ip_off) & 0x1fff);
	(void)printf("  %02x  %02x %04x", ip->ip_ttl, ip->ip_p,
							    ntohs(ip->ip_sum));
	memcpy(&ina, &ip->ip_src.s_addr, sizeof ina);
	(void)printf(" %s ", inet_ntoa(ina));
	memcpy(&ina, &ip->ip_dst.s_addr, sizeof ina);
	(void)printf(" %s ", inet_ntoa(ina));
	/* dump any option bytes */
	while (hlen-- > 20) {
		(void)printf("%02x", *cp++);
	}
	(void)putchar('\n');
}