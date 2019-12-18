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
struct rt_spare {scalar_t__ rts_router; scalar_t__ rts_gate; int /*<<< orphan*/  rts_time; int /*<<< orphan*/  rts_metric; struct interface* rts_ifp; } ;
struct rt_entry {scalar_t__ rt_router; int rt_state; struct interface* rt_ifp; } ;
struct interface {int int_state; int int_if_flags; scalar_t__ int_addr; int /*<<< orphan*/  int_mask; int /*<<< orphan*/  int_name; int /*<<< orphan*/  int_transitions; int /*<<< orphan*/  int_metric; int /*<<< orphan*/  int_net; int /*<<< orphan*/  int_dstaddr; } ;
typedef  int /*<<< orphan*/  naddr ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_POINTOPOINT ; 
 int IS_BROKE ; 
 int IS_DUP ; 
 int IS_EXTERNAL ; 
 int IS_REMOTE ; 
 int IS_SUBNET ; 
 int RS_IF ; 
 int RS_LOCAL ; 
 int RS_NET_SYN ; 
 int /*<<< orphan*/  check_net_syn (struct interface*) ; 
 int /*<<< orphan*/  check_remote (struct interface*) ; 
 int /*<<< orphan*/  del_static (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_1__ now ; 
 int /*<<< orphan*/  rtadd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct rt_spare*) ; 
 int /*<<< orphan*/  rtchange (struct rt_entry*,int,struct rt_spare*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtdelete (struct rt_entry*) ; 
 struct rt_entry* rtget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_act (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int					/* 0=bad interface */
addrouteforif(struct interface *ifp)
{
	struct rt_entry *rt;
	static struct rt_spare new;
	naddr dst;


	/* skip sick interfaces
	 */
	if (ifp->int_state & IS_BROKE)
		return 0;

	/* If the interface on a subnet, then install a RIPv1 route to
	 * the network as well (unless it is sick).
	 */
	if (ifp->int_state & IS_SUBNET)
		check_net_syn(ifp);

	dst = (0 != (ifp->int_if_flags & (IFF_POINTOPOINT | IFF_LOOPBACK))
	       ? ifp->int_dstaddr
	       : htonl(ifp->int_net));

	new.rts_ifp = ifp;
	new.rts_router = ifp->int_addr;
	new.rts_gate = ifp->int_addr;
	new.rts_metric = ifp->int_metric;
	new.rts_time = now.tv_sec;

	/* If we are going to send packets to the gateway,
	 * it must be reachable using our physical interfaces
	 */
	if ((ifp->int_state & IS_REMOTE)
	    && !(ifp->int_state & IS_EXTERNAL)
	    && !check_remote(ifp))
		return 0;

	/* We are finished if the correct main interface route exists.
	 * The right route must be for the right interface, not synthesized
	 * from a subnet, be a "gateway" or not as appropriate, and so forth.
	 */
	del_static(dst, ifp->int_mask, 0, 0);
	rt = rtget(dst, ifp->int_mask);
	if (rt != NULL) {
		if ((rt->rt_ifp != ifp
		     || rt->rt_router != ifp->int_addr)
		    && (!(ifp->int_state & IS_DUP)
			|| rt->rt_ifp == 0
			|| (rt->rt_ifp->int_state & IS_BROKE))) {
			rtdelete(rt);
			rt = NULL;
		} else {
			rtchange(rt, ((rt->rt_state | RS_IF)
				      & ~(RS_NET_SYN | RS_LOCAL)),
				 &new, 0);
		}
	}
	if (rt == NULL) {
		if (ifp->int_transitions++ > 0)
			trace_act("re-install interface %s",
				  ifp->int_name);

		rtadd(dst, ifp->int_mask, RS_IF, &new);
	}

	return 1;
}