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
struct nat64lsn_state {int proto; int /*<<< orphan*/  flags; int /*<<< orphan*/  timestamp; } ;
struct nat64lsn_cfg {int st_close_ttl; int st_estab_ttl; int st_syn_ttl; int st_udp_ttl; int st_icmp_ttl; } ;

/* Variables and functions */
 int GET_AGE (int /*<<< orphan*/ ) ; 
#define  IPPROTO_ICMP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 scalar_t__ ISSET32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAT64_BIT_READY_IPV4 ; 
 int /*<<< orphan*/  NAT64_BIT_STALE ; 
 int /*<<< orphan*/  NAT64_BIT_TCP_ESTAB ; 
 int /*<<< orphan*/  NAT64_BIT_TCP_FIN ; 
 int /*<<< orphan*/  NAT64_BIT_TCP_SYN ; 

__attribute__((used)) static int
nat64lsn_check_state(struct nat64lsn_cfg *cfg, struct nat64lsn_state *state)
{
	int age, ttl;

	/* State was marked as stale in previous pass. */
	if (ISSET32(state->flags, NAT64_BIT_STALE))
		return (1);

	/* State is not yet initialized, it is going to be READY */
	if (!ISSET32(state->flags, NAT64_BIT_READY_IPV4))
		return (0);

	age = GET_AGE(state->timestamp);
	switch (state->proto) {
	case IPPROTO_TCP:
		if (ISSET32(state->flags, NAT64_BIT_TCP_FIN))
			ttl = cfg->st_close_ttl;
		else if (ISSET32(state->flags, NAT64_BIT_TCP_ESTAB))
			ttl = cfg->st_estab_ttl;
		else if (ISSET32(state->flags, NAT64_BIT_TCP_SYN))
			ttl = cfg->st_syn_ttl;
		else
			ttl = cfg->st_syn_ttl;
		if (age > ttl)
			return (1);
		break;
	case IPPROTO_UDP:
		if (age > cfg->st_udp_ttl)
			return (1);
		break;
	case IPPROTO_ICMP:
		if (age > cfg->st_icmp_ttl)
			return (1);
		break;
	}
	return (0);
}