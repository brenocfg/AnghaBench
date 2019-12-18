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
typedef  int uint32_t ;
struct pfloghdr {char* ruleset; int /*<<< orphan*/  ifname; void* subrulenr; void* rulenr; int /*<<< orphan*/  dir; int /*<<< orphan*/  action; int /*<<< orphan*/  af; int /*<<< orphan*/  length; } ;
struct nat64lsn_state {int ip_src; int aport; int proto; int ip_dst; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFLOG_HDRLEN ; 
 int /*<<< orphan*/  PFLOG_REAL_HDRLEN ; 
 int /*<<< orphan*/  PF_IN ; 
 int /*<<< orphan*/  PF_NAT ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  ipfw_bpf_mtap2 (struct pfloghdr*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  memset (struct pfloghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
nat64lsn_log(struct pfloghdr *plog, struct mbuf *m, sa_family_t family,
    struct nat64lsn_state *state)
{

	memset(plog, 0, sizeof(*plog));
	plog->length = PFLOG_REAL_HDRLEN;
	plog->af = family;
	plog->action = PF_NAT;
	plog->dir = PF_IN;
	plog->rulenr = htonl(state->ip_src);
	plog->subrulenr = htonl((uint32_t)(state->aport << 16) |
	    (state->proto << 8) | (state->ip_dst & 0xff));
	plog->ruleset[0] = '\0';
	strlcpy(plog->ifname, "NAT64LSN", sizeof(plog->ifname));
	ipfw_bpf_mtap2(plog, PFLOG_HDRLEN, m);
}