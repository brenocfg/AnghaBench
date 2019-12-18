#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ u_int8_t ;
struct pf_state_key_cmp {int* port; int /*<<< orphan*/  af; int /*<<< orphan*/ * addr; scalar_t__ proto; } ;
struct pf_src_node {int dummy; } ;
struct TYPE_2__ {int opts; } ;
struct pf_rule {TYPE_1__ rpool; } ;
struct pf_addr {int* port; int /*<<< orphan*/  af; int /*<<< orphan*/ * addr; scalar_t__ proto; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  init_addr ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,struct pf_state_key_cmp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_AEQ (struct pf_state_key_cmp*,struct pf_state_key_cmp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_IN ; 
#define  PF_POOL_BITMASK 132 
#define  PF_POOL_NONE 131 
#define  PF_POOL_RANDOM 130 
#define  PF_POOL_ROUNDROBIN 129 
#define  PF_POOL_SRCHASH 128 
 int PF_POOL_TYPEMASK ; 
 int arc4random () ; 
 int /*<<< orphan*/  bzero (struct pf_state_key_cmp*,int) ; 
 void* htons (int) ; 
 int /*<<< orphan*/ * pf_find_state_all (struct pf_state_key_cmp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pf_map_addr (int /*<<< orphan*/ ,struct pf_rule*,struct pf_state_key_cmp*,struct pf_state_key_cmp*,struct pf_state_key_cmp*,struct pf_src_node**) ; 

__attribute__((used)) static int
pf_get_sport(sa_family_t af, u_int8_t proto, struct pf_rule *r,
    struct pf_addr *saddr, uint16_t sport, struct pf_addr *daddr,
    uint16_t dport, struct pf_addr *naddr, uint16_t *nport, uint16_t low,
    uint16_t high, struct pf_src_node **sn)
{
	struct pf_state_key_cmp	key;
	struct pf_addr		init_addr;

	bzero(&init_addr, sizeof(init_addr));
	if (pf_map_addr(af, r, saddr, naddr, &init_addr, sn))
		return (1);

	if (proto == IPPROTO_ICMP) {
		low = 1;
		high = 65535;
	}

	bzero(&key, sizeof(key));
	key.af = af;
	key.proto = proto;
	key.port[0] = dport;
	PF_ACPY(&key.addr[0], daddr, key.af);

	do {
		PF_ACPY(&key.addr[1], naddr, key.af);

		/*
		 * port search; start random, step;
		 * similar 2 portloop in in_pcbbind
		 */
		if (!(proto == IPPROTO_TCP || proto == IPPROTO_UDP ||
		    proto == IPPROTO_ICMP) || (low == 0 && high == 0)) {
			/*
			 * XXX bug: icmp states don't use the id on both sides.
			 * (traceroute -I through nat)
			 */
			key.port[1] = sport;
			if (pf_find_state_all(&key, PF_IN, NULL) == NULL) {
				*nport = sport;
				return (0);
			}
		} else if (low == high) {
			key.port[1] = htons(low);
			if (pf_find_state_all(&key, PF_IN, NULL) == NULL) {
				*nport = htons(low);
				return (0);
			}
		} else {
			uint32_t tmp;
			uint16_t cut;

			if (low > high) {
				tmp = low;
				low = high;
				high = tmp;
			}
			/* low < high */
			cut = arc4random() % (1 + high - low) + low;
			/* low <= cut <= high */
			for (tmp = cut; tmp <= high && tmp <= 0xffff; ++tmp) {
				key.port[1] = htons(tmp);
				if (pf_find_state_all(&key, PF_IN, NULL) ==
				    NULL) {
					*nport = htons(tmp);
					return (0);
				}
			}
			tmp = cut;
			for (tmp -= 1; tmp >= low && tmp <= 0xffff; --tmp) {
				key.port[1] = htons(tmp);
				if (pf_find_state_all(&key, PF_IN, NULL) ==
				    NULL) {
					*nport = htons(tmp);
					return (0);
				}
			}
		}

		switch (r->rpool.opts & PF_POOL_TYPEMASK) {
		case PF_POOL_RANDOM:
		case PF_POOL_ROUNDROBIN:
			/*
			 * pick a different source address since we're out
			 * of free port choices for the current one.
			 */
			if (pf_map_addr(af, r, saddr, naddr, &init_addr, sn))
				return (1);
			break;
		case PF_POOL_NONE:
		case PF_POOL_SRCHASH:
		case PF_POOL_BITMASK:
		default:
			return (1);
		}
	} while (! PF_AEQ(&init_addr, naddr, af) );
	return (1);					/* none available */
}