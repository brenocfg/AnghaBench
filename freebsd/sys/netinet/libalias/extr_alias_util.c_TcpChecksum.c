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
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_char ;
struct tcphdr {int dummy; } ;
struct ip {int ip_hl; scalar_t__ ip_p; int /*<<< orphan*/  ip_src; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_len; } ;

/* Variables and functions */
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ ip_next (struct ip*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

u_short
TcpChecksum(struct ip *pip)
{
	u_short *ptr;
	struct tcphdr *tc;
	int nhdr, ntcp, nbytes;
	int sum, oddbyte;

	nhdr = pip->ip_hl << 2;
	ntcp = ntohs(pip->ip_len) - nhdr;

	tc = (struct tcphdr *)ip_next(pip);
	ptr = (u_short *) tc;

/* Add up TCP header and data */
	nbytes = ntcp;
	sum = 0;
	while (nbytes > 1) {
		sum += *ptr++;
		nbytes -= 2;
	}
	if (nbytes == 1) {
		oddbyte = 0;
		((u_char *) & oddbyte)[0] = *(u_char *) ptr;
		((u_char *) & oddbyte)[1] = 0;
		sum += oddbyte;
	}
/* "Pseudo-header" data */
	ptr = (void *)&pip->ip_dst;
	sum += *ptr++;
	sum += *ptr;
	ptr = (void *)&pip->ip_src;
	sum += *ptr++;
	sum += *ptr;
	sum += htons((u_short) ntcp);
	sum += htons((u_short) pip->ip_p);

/* Roll over carry bits */
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);

/* Return checksum */
	return ((u_short) ~ sum);
}