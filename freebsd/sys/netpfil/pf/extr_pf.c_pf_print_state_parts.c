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
typedef  int u_int8_t ;
struct pf_state_key {int proto; int /*<<< orphan*/  af; int /*<<< orphan*/ * port; int /*<<< orphan*/ * addr; } ;
struct TYPE_4__ {int wscale; int seqlo; int seqhi; int max_win; int seqdiff; int state; } ;
struct TYPE_3__ {int seqlo; int seqhi; int max_win; int seqdiff; int wscale; int state; } ;
struct pf_state {int direction; TYPE_2__ dst; TYPE_1__ src; struct pf_state_key** key; } ;

/* Variables and functions */
#define  IPPROTO_ICMP 135 
#define  IPPROTO_ICMPV6 134 
#define  IPPROTO_IPV4 133 
#define  IPPROTO_IPV6 132 
#define  IPPROTO_TCP 131 
#define  IPPROTO_UDP 130 
#define  PF_IN 129 
#define  PF_OUT 128 
 size_t PF_SK_STACK ; 
 size_t PF_SK_WIRE ; 
 int PF_WSCALE_MASK ; 
 int /*<<< orphan*/  pf_print_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
pf_print_state_parts(struct pf_state *s,
    struct pf_state_key *skwp, struct pf_state_key *sksp)
{
	struct pf_state_key *skw, *sks;
	u_int8_t proto, dir;

	/* Do our best to fill these, but they're skipped if NULL */
	skw = skwp ? skwp : (s ? s->key[PF_SK_WIRE] : NULL);
	sks = sksp ? sksp : (s ? s->key[PF_SK_STACK] : NULL);
	proto = skw ? skw->proto : (sks ? sks->proto : 0);
	dir = s ? s->direction : 0;

	switch (proto) {
	case IPPROTO_IPV4:
		printf("IPv4");
		break;
	case IPPROTO_IPV6:
		printf("IPv6");
		break;
	case IPPROTO_TCP:
		printf("TCP");
		break;
	case IPPROTO_UDP:
		printf("UDP");
		break;
	case IPPROTO_ICMP:
		printf("ICMP");
		break;
	case IPPROTO_ICMPV6:
		printf("ICMPv6");
		break;
	default:
		printf("%u", proto);
		break;
	}
	switch (dir) {
	case PF_IN:
		printf(" in");
		break;
	case PF_OUT:
		printf(" out");
		break;
	}
	if (skw) {
		printf(" wire: ");
		pf_print_host(&skw->addr[0], skw->port[0], skw->af);
		printf(" ");
		pf_print_host(&skw->addr[1], skw->port[1], skw->af);
	}
	if (sks) {
		printf(" stack: ");
		if (sks != skw) {
			pf_print_host(&sks->addr[0], sks->port[0], sks->af);
			printf(" ");
			pf_print_host(&sks->addr[1], sks->port[1], sks->af);
		} else
			printf("-");
	}
	if (s) {
		if (proto == IPPROTO_TCP) {
			printf(" [lo=%u high=%u win=%u modulator=%u",
			    s->src.seqlo, s->src.seqhi,
			    s->src.max_win, s->src.seqdiff);
			if (s->src.wscale && s->dst.wscale)
				printf(" wscale=%u",
				    s->src.wscale & PF_WSCALE_MASK);
			printf("]");
			printf(" [lo=%u high=%u win=%u modulator=%u",
			    s->dst.seqlo, s->dst.seqhi,
			    s->dst.max_win, s->dst.seqdiff);
			if (s->src.wscale && s->dst.wscale)
				printf(" wscale=%u",
				s->dst.wscale & PF_WSCALE_MASK);
			printf("]");
		}
		printf(" %u:%u", s->src.state, s->dst.state);
	}
}