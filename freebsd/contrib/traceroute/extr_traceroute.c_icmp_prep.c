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
typedef  int /*<<< orphan*/  u_short ;
struct outdata {int /*<<< orphan*/  seq; } ;
struct icmp {int icmp_cksum; void* icmp_seq; void* icmp_id; int /*<<< orphan*/  icmp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_ECHO ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident ; 
 int in_cksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ outp ; 
 int /*<<< orphan*/  protlen ; 

void
icmp_prep(struct outdata *outdata)
{
	struct icmp *const icmpheader = (struct icmp *) outp;

	icmpheader->icmp_type = ICMP_ECHO;
	icmpheader->icmp_id = htons(ident);
	icmpheader->icmp_seq = htons(outdata->seq);
	icmpheader->icmp_cksum = 0;
	icmpheader->icmp_cksum = in_cksum((u_short *)icmpheader, protlen);
	if (icmpheader->icmp_cksum == 0)
		icmpheader->icmp_cksum = 0xffff;
}