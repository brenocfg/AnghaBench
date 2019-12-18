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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct pfloghdr {int dummy; } ;
struct nat64lsn_state {scalar_t__ timestamp; int flags; int /*<<< orphan*/  aport; int /*<<< orphan*/  ip_src; } ;
struct TYPE_2__ {int flags; } ;
struct nat64lsn_cfg {int nomatch_verdict; TYPE_1__ base; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int IP_FW_DENY ; 
 int NAT64RETURN ; 
 int NAT64SKIP ; 
 int NAT64_LOG ; 
 int /*<<< orphan*/  SET_AGE (scalar_t__) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int nat64_do_handle_ip6 (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct pfloghdr*) ; 
 int /*<<< orphan*/  nat64lsn_log (struct pfloghdr*,struct mbuf*,int /*<<< orphan*/ ,struct nat64lsn_state*) ; 

__attribute__((used)) static int
nat64lsn_translate6_internal(struct nat64lsn_cfg *cfg, struct mbuf **mp,
    struct nat64lsn_state *state, uint8_t flags)
{
	struct pfloghdr loghdr, *logdata;
	int ret;
	uint16_t ts;

	/* Update timestamp and flags if needed */
	SET_AGE(ts);
	if (state->timestamp != ts)
		state->timestamp = ts;
	if ((state->flags & flags) != 0)
		state->flags |= flags;

	if (cfg->base.flags & NAT64_LOG) {
		logdata = &loghdr;
		nat64lsn_log(logdata, *mp, AF_INET6, state);
	} else
		logdata = NULL;

	ret = nat64_do_handle_ip6(*mp, htonl(state->ip_src),
	    htons(state->aport), &cfg->base, logdata);
	if (ret == NAT64SKIP)
		return (cfg->nomatch_verdict);
	if (ret == NAT64RETURN)
		*mp = NULL;
	return (IP_FW_DENY);
}