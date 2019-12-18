#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct sctp_tcb {int dummy; } ;
struct sctp_nets {int addr_is_local; } ;
struct sctp_inpcb {int sctp_flags; int /*<<< orphan*/  fibnum; } ;
struct sctp_ifa {int dummy; } ;
struct TYPE_9__ {int sa_family; } ;
struct TYPE_10__ {TYPE_1__ ro_dst; int /*<<< orphan*/ * ro_rt; } ;
typedef  TYPE_2__ sctp_route_t ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN4_ISLOOPBACK_ADDRESS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN4_ISPRIVATE_ADDRESS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  SCTP_DEBUG_OUTPUT2 ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_RLOCK () ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_RUNLOCK () ; 
 int SCTP_PCB_FLAGS_BOUNDALL ; 
 int /*<<< orphan*/  SCTP_ROUTE_IS_REAL_LOOP (TYPE_2__*) ; 
 int /*<<< orphan*/  SCTP_RTALLOC (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_ifa* sctp_choose_boundall (struct sctp_inpcb*,struct sctp_tcb*,struct sctp_nets*,TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct sctp_ifa* sctp_choose_boundspecific_inp (struct sctp_inpcb*,TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct sctp_ifa* sctp_choose_boundspecific_stcb (struct sctp_inpcb*,struct sctp_tcb*,TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int) ; 

struct sctp_ifa *
sctp_source_address_selection(struct sctp_inpcb *inp,
    struct sctp_tcb *stcb,
    sctp_route_t *ro,
    struct sctp_nets *net,
    int non_asoc_addr_ok, uint32_t vrf_id)
{
	struct sctp_ifa *answer;
	uint8_t dest_is_priv, dest_is_loop;
	sa_family_t fam;
#ifdef INET
	struct sockaddr_in *to = (struct sockaddr_in *)&ro->ro_dst;
#endif
#ifdef INET6
	struct sockaddr_in6 *to6 = (struct sockaddr_in6 *)&ro->ro_dst;
#endif

	/**
	 * Rules:
	 * - Find the route if needed, cache if I can.
	 * - Look at interface address in route, Is it in the bound list. If so we
	 *   have the best source.
	 * - If not we must rotate amongst the addresses.
	 *
	 * Cavets and issues
	 *
	 * Do we need to pay attention to scope. We can have a private address
	 * or a global address we are sourcing or sending to. So if we draw
	 * it out
	 * zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
	 * For V4
	 * ------------------------------------------
	 *      source     *      dest  *  result
	 * -----------------------------------------
	 * <a>  Private    *    Global  *  NAT
	 * -----------------------------------------
	 * <b>  Private    *    Private *  No problem
	 * -----------------------------------------
	 * <c>  Global     *    Private *  Huh, How will this work?
	 * -----------------------------------------
	 * <d>  Global     *    Global  *  No Problem
	 *------------------------------------------
	 * zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
	 * For V6
	 *------------------------------------------
	 *      source     *      dest  *  result
	 * -----------------------------------------
	 * <a>  Linklocal  *    Global  *
	 * -----------------------------------------
	 * <b>  Linklocal  * Linklocal  *  No problem
	 * -----------------------------------------
	 * <c>  Global     * Linklocal  *  Huh, How will this work?
	 * -----------------------------------------
	 * <d>  Global     *    Global  *  No Problem
	 *------------------------------------------
	 * zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
	 *
	 * And then we add to that what happens if there are multiple addresses
	 * assigned to an interface. Remember the ifa on a ifn is a linked
	 * list of addresses. So one interface can have more than one IP
	 * address. What happens if we have both a private and a global
	 * address? Do we then use context of destination to sort out which
	 * one is best? And what about NAT's sending P->G may get you a NAT
	 * translation, or should you select the G thats on the interface in
	 * preference.
	 *
	 * Decisions:
	 *
	 * - count the number of addresses on the interface.
	 * - if it is one, no problem except case <c>.
	 *   For <a> we will assume a NAT out there.
	 * - if there are more than one, then we need to worry about scope P
	 *   or G. We should prefer G -> G and P -> P if possible.
	 *   Then as a secondary fall back to mixed types G->P being a last
	 *   ditch one.
	 * - The above all works for bound all, but bound specific we need to
	 *   use the same concept but instead only consider the bound
	 *   addresses. If the bound set is NOT assigned to the interface then
	 *   we must use rotation amongst the bound addresses..
	 */
	if (ro->ro_rt == NULL) {
		/*
		 * Need a route to cache.
		 */
		SCTP_RTALLOC(ro, vrf_id, inp->fibnum);
	}
	if (ro->ro_rt == NULL) {
		return (NULL);
	}
	fam = ro->ro_dst.sa_family;
	dest_is_priv = dest_is_loop = 0;
	/* Setup our scopes for the destination */
	switch (fam) {
#ifdef INET
	case AF_INET:
		/* Scope based on outbound address */
		if (IN4_ISLOOPBACK_ADDRESS(&to->sin_addr)) {
			dest_is_loop = 1;
			if (net != NULL) {
				/* mark it as local */
				net->addr_is_local = 1;
			}
		} else if ((IN4_ISPRIVATE_ADDRESS(&to->sin_addr))) {
			dest_is_priv = 1;
		}
		break;
#endif
#ifdef INET6
	case AF_INET6:
		/* Scope based on outbound address */
		if (IN6_IS_ADDR_LOOPBACK(&to6->sin6_addr) ||
		    SCTP_ROUTE_IS_REAL_LOOP(ro)) {
			/*
			 * If the address is a loopback address, which
			 * consists of "::1" OR "fe80::1%lo0", we are
			 * loopback scope. But we don't use dest_is_priv
			 * (link local addresses).
			 */
			dest_is_loop = 1;
			if (net != NULL) {
				/* mark it as local */
				net->addr_is_local = 1;
			}
		} else if (IN6_IS_ADDR_LINKLOCAL(&to6->sin6_addr)) {
			dest_is_priv = 1;
		}
		break;
#endif
	}
	SCTPDBG(SCTP_DEBUG_OUTPUT2, "Select source addr for:");
	SCTPDBG_ADDR(SCTP_DEBUG_OUTPUT2, (struct sockaddr *)&ro->ro_dst);
	SCTP_IPI_ADDR_RLOCK();
	if (inp->sctp_flags & SCTP_PCB_FLAGS_BOUNDALL) {
		/*
		 * Bound all case
		 */
		answer = sctp_choose_boundall(inp, stcb, net, ro, vrf_id,
		    dest_is_priv, dest_is_loop,
		    non_asoc_addr_ok, fam);
		SCTP_IPI_ADDR_RUNLOCK();
		return (answer);
	}
	/*
	 * Subset bound case
	 */
	if (stcb) {
		answer = sctp_choose_boundspecific_stcb(inp, stcb, ro,
		    vrf_id, dest_is_priv,
		    dest_is_loop,
		    non_asoc_addr_ok, fam);
	} else {
		answer = sctp_choose_boundspecific_inp(inp, ro, vrf_id,
		    non_asoc_addr_ok,
		    dest_is_priv,
		    dest_is_loop, fam);
	}
	SCTP_IPI_ADDR_RUNLOCK();
	return (answer);
}