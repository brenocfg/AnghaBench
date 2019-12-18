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
typedef  int u_short ;
struct udphdr {int uh_sum; void* uh_ulen; void* uh_dport; void* uh_sport; } ;
struct outdata {int seq; } ;

/* Variables and functions */
 scalar_t__ doipcksum ; 
 scalar_t__ fixedPort ; 
 void* htons (int) ; 
 int ident ; 
 int /*<<< orphan*/  outip ; 
 scalar_t__ outp ; 
 int p_cksum (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int port ; 
 int /*<<< orphan*/  protlen ; 

void
udplite_prep(struct outdata *outdata)
{
	struct udphdr *const outudp = (struct udphdr *) outp;

	outudp->uh_sport = htons(ident + (fixedPort ? outdata->seq : 0));
	outudp->uh_dport = htons(port + (fixedPort ? 0 : outdata->seq));
	outudp->uh_ulen = htons(8);
	outudp->uh_sum = 0;
	if (doipcksum) {
	    u_short sum = p_cksum(outip, (u_short*)outudp, protlen, 8);
	    outudp->uh_sum = (sum) ? sum : 0xffff;
	}

	return;
}