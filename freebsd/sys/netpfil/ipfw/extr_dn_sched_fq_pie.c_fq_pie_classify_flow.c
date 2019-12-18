#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct udphdr {int uh_dport; int uh_sport; } ;
struct tcphdr {int th_dport; int th_sport; } ;
struct mbuf {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s6_addr; } ;
struct ip6_hdr {int ip6_nxt; TYPE_2__ ip6_dst; TYPE_1__ ip6_src; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_v; int ip_p; TYPE_4__ ip_dst; TYPE_3__ ip_src; } ;
struct fq_pie_si {int /*<<< orphan*/  perturbation; } ;
struct TYPE_10__ {int /*<<< orphan*/  iphdr_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASHINIT ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 TYPE_5__* dn_tag_get (struct mbuf*) ; 
 int jenkins_hash (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mtodo (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
fq_pie_classify_flow(struct mbuf *m, uint16_t fcount, struct fq_pie_si *si)
{
	struct ip *ip;
	struct tcphdr *th;
	struct udphdr *uh;
	uint8_t tuple[41];
	uint16_t hash=0;

	ip = (struct ip *)mtodo(m, dn_tag_get(m)->iphdr_off);
//#ifdef INET6
	struct ip6_hdr *ip6;
	int isip6;
	isip6 = (ip->ip_v == 6);

	if(isip6) {
		ip6 = (struct ip6_hdr *)ip;
		*((uint8_t *) &tuple[0]) = ip6->ip6_nxt;
		*((uint32_t *) &tuple[1]) = si->perturbation;
		memcpy(&tuple[5], ip6->ip6_src.s6_addr, 16);
		memcpy(&tuple[21], ip6->ip6_dst.s6_addr, 16);

		switch (ip6->ip6_nxt) {
		case IPPROTO_TCP:
			th = (struct tcphdr *)(ip6 + 1);
			*((uint16_t *) &tuple[37]) = th->th_dport;
			*((uint16_t *) &tuple[39]) = th->th_sport;
			break;

		case IPPROTO_UDP:
			uh = (struct udphdr *)(ip6 + 1);
			*((uint16_t *) &tuple[37]) = uh->uh_dport;
			*((uint16_t *) &tuple[39]) = uh->uh_sport;
			break;
		default:
			memset(&tuple[37], 0, 4);
		}

		hash = jenkins_hash(tuple, 41, HASHINIT) %  fcount;
		return hash;
	} 
//#endif

	/* IPv4 */
	*((uint8_t *) &tuple[0]) = ip->ip_p;
	*((uint32_t *) &tuple[1]) = si->perturbation;
	*((uint32_t *) &tuple[5]) = ip->ip_src.s_addr;
	*((uint32_t *) &tuple[9]) = ip->ip_dst.s_addr;

	switch (ip->ip_p) {
		case IPPROTO_TCP:
			th = (struct tcphdr *)(ip + 1);
			*((uint16_t *) &tuple[13]) = th->th_dport;
			*((uint16_t *) &tuple[15]) = th->th_sport;
			break;

		case IPPROTO_UDP:
			uh = (struct udphdr *)(ip + 1);
			*((uint16_t *) &tuple[13]) = uh->uh_dport;
			*((uint16_t *) &tuple[15]) = uh->uh_sport;
			break;
		default:
			memset(&tuple[13], 0, 4);
	}
	hash = jenkins_hash(tuple, 17, HASHINIT) % fcount;

	return hash;
}