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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct pfsync_state_peer {int dummy; } ;
struct pfsync_state_key {scalar_t__* port; int /*<<< orphan*/ * addr; } ;
struct pfsync_state {scalar_t__ direction; int creation; int expire; int anchor; int rule; int creatorid; int /*<<< orphan*/  id; int /*<<< orphan*/ ** bytes; int /*<<< orphan*/ ** packets; int /*<<< orphan*/  proto; int /*<<< orphan*/  af; int /*<<< orphan*/  ifname; struct pfsync_state_key* key; struct pfsync_state_peer src; struct pfsync_state_peer dst; } ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ PF_ANEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PF_OUT ; 
 size_t PF_SK_STACK ; 
 size_t PF_SK_WIRE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  print_host (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_src_dst (TYPE_1__*,struct pfsync_state_peer*,struct pfsync_state_peer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_state(netdissect_options *ndo, struct pfsync_state *s)
{
	struct pfsync_state_peer *src, *dst;
	struct pfsync_state_key *sk, *nk;
	int min, sec;

	if (s->direction == PF_OUT) {
		src = &s->src;
		dst = &s->dst;
		sk = &s->key[PF_SK_STACK];
		nk = &s->key[PF_SK_WIRE];
		if (s->proto == IPPROTO_ICMP || s->proto == IPPROTO_ICMPV6)
			sk->port[0] = nk->port[0];
	} else {
		src = &s->dst;
		dst = &s->src;
		sk = &s->key[PF_SK_WIRE];
		nk = &s->key[PF_SK_STACK];
		if (s->proto == IPPROTO_ICMP || s->proto == IPPROTO_ICMPV6)
			sk->port[1] = nk->port[1];
	}
	ND_PRINT((ndo, "\t%s ", s->ifname));
	ND_PRINT((ndo, "proto %u ", s->proto));

	print_host(ndo, &nk->addr[1], nk->port[1], s->af, NULL);
	if (PF_ANEQ(&nk->addr[1], &sk->addr[1], s->af) ||
	    nk->port[1] != sk->port[1]) {
		ND_PRINT((ndo, " ("));
		print_host(ndo, &sk->addr[1], sk->port[1], s->af, NULL);
		ND_PRINT((ndo, ")"));
	}
	if (s->direction == PF_OUT)
		ND_PRINT((ndo, " -> "));
	else
		ND_PRINT((ndo, " <- "));
	print_host(ndo, &nk->addr[0], nk->port[0], s->af, NULL);
	if (PF_ANEQ(&nk->addr[0], &sk->addr[0], s->af) ||
	    nk->port[0] != sk->port[0]) {
		ND_PRINT((ndo, " ("));
		print_host(ndo, &sk->addr[0], sk->port[0], s->af, NULL);
		ND_PRINT((ndo, ")"));
	}

	print_src_dst(ndo, src, dst, s->proto);

	if (ndo->ndo_vflag > 1) {
		uint64_t packets[2];
		uint64_t bytes[2];
		uint32_t creation = ntohl(s->creation);
		uint32_t expire = ntohl(s->expire);

		sec = creation % 60;
		creation /= 60;
		min = creation % 60;
		creation /= 60;
		ND_PRINT((ndo, "\n\tage %.2u:%.2u:%.2u", creation, min, sec));
		sec = expire % 60;
		expire /= 60;
		min = expire % 60;
		expire /= 60;
		ND_PRINT((ndo, ", expires in %.2u:%.2u:%.2u", expire, min, sec));

		bcopy(s->packets[0], &packets[0], sizeof(uint64_t));
		bcopy(s->packets[1], &packets[1], sizeof(uint64_t));
		bcopy(s->bytes[0], &bytes[0], sizeof(uint64_t));
		bcopy(s->bytes[1], &bytes[1], sizeof(uint64_t));
		ND_PRINT((ndo, ", %ju:%ju pkts, %ju:%ju bytes",
		    be64toh(packets[0]), be64toh(packets[1]),
		    be64toh(bytes[0]), be64toh(bytes[1])));
		if (s->anchor != ntohl(-1))
			ND_PRINT((ndo, ", anchor %u", ntohl(s->anchor)));
		if (s->rule != ntohl(-1))
			ND_PRINT((ndo, ", rule %u", ntohl(s->rule)));
	}
	if (ndo->ndo_vflag > 1) {
		uint64_t id;

		bcopy(&s->id, &id, sizeof(uint64_t));
		ND_PRINT((ndo, "\n\tid: %016jx creatorid: %08x",
		    (uintmax_t )be64toh(id), ntohl(s->creatorid)));
	}
}