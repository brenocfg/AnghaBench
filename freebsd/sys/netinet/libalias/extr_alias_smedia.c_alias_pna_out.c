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
typedef  char u_short ;
struct tcphdr {int th_x2; scalar_t__ th_sum; } ;
struct libalias {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_src; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 struct alias_link* FindUdpTcpOut (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char GetAliasPort (struct alias_link*) ; 
 int /*<<< orphan*/  GetDestAddress (struct alias_link*) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PunchFWHole (struct alias_link*) ; 
 scalar_t__ TcpChecksum (struct ip*) ; 
 scalar_t__ ip_next (struct ip*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ntohs (char) ; 

__attribute__((used)) static int
alias_pna_out(struct libalias *la, struct ip *pip,
    struct alias_link *lnk,
    char *data,
    int dlen)
{
	struct alias_link *pna_links;
	u_short msg_id, msg_len;
	char *work;
	u_short alias_port, port;
	struct tcphdr *tc;

	work = data;
	work += 5;
	while (work + 4 < data + dlen) {
		memcpy(&msg_id, work, 2);
		work += 2;
		memcpy(&msg_len, work, 2);
		work += 2;
		if (ntohs(msg_id) == 0) {
			/* end of options */
			return (0);
		}
		if ((ntohs(msg_id) == 1) || (ntohs(msg_id) == 7)) {
			memcpy(&port, work, 2);
			pna_links = FindUdpTcpOut(la, pip->ip_src, GetDestAddress(lnk),
			    port, 0, IPPROTO_UDP, 1);
			if (pna_links != NULL) {
#ifndef NO_FW_PUNCH
				/* Punch hole in firewall */
				PunchFWHole(pna_links);
#endif
				tc = (struct tcphdr *)ip_next(pip);
				alias_port = GetAliasPort(pna_links);
				memcpy(work, &alias_port, 2);

				/* Compute TCP checksum for revised packet */
				tc->th_sum = 0;
#ifdef _KERNEL
				tc->th_x2 = 1;
#else
				tc->th_sum = TcpChecksum(pip);
#endif
			}
		}
		work += ntohs(msg_len);
	}

	return (0);
}