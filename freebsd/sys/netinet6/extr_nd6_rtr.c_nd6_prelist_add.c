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
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; } ;
struct nd_prefixctl {int /*<<< orphan*/  ndpr_ifp; int /*<<< orphan*/  ndpr_plen; TYPE_1__ ndpr_prefix; int /*<<< orphan*/  ndpr_flags; int /*<<< orphan*/  ndpr_pltime; int /*<<< orphan*/  ndpr_vltime; } ;
struct nd_prefix {scalar_t__ ndpr_raf_onlink; int /*<<< orphan*/  ndpr_mask; TYPE_1__ ndpr_prefix; int /*<<< orphan*/  ndpr_plen; int /*<<< orphan*/  ndpr_advrtrs; int /*<<< orphan*/  ndpr_lastupdate; int /*<<< orphan*/  ndpr_flags; int /*<<< orphan*/  ndpr_pltime; int /*<<< orphan*/  ndpr_vltime; int /*<<< orphan*/  ndpr_ifp; int /*<<< orphan*/  ndpr_refcnt; } ;
struct nd_defrouter {int dummy; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IN6_MASK_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nd_prefix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  M_IP6NDP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ND6_ONLINK_LOCK () ; 
 int /*<<< orphan*/  ND6_ONLINK_UNLOCK () ; 
 int /*<<< orphan*/  ND6_WLOCK () ; 
 int /*<<< orphan*/  ND6_WUNLOCK () ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  V_nd6_list_genid ; 
 int /*<<< orphan*/  V_nd_prefix ; 
 int /*<<< orphan*/  free (struct nd_prefix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int in6_init_prefix_ltimes (struct nd_prefix*) ; 
 int /*<<< orphan*/  in6_prefixlen2mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_sprintf (char*,int /*<<< orphan*/ *) ; 
 struct nd_prefix* malloc (int,int /*<<< orphan*/ ,int) ; 
 int nd6_prefix_onlink (struct nd_prefix*) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndpr_entry ; 
 int /*<<< orphan*/  pfxrtr_add (struct nd_prefix*,struct nd_defrouter*) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  time_uptime ; 

int
nd6_prelist_add(struct nd_prefixctl *pr, struct nd_defrouter *dr,
    struct nd_prefix **newp)
{
	struct nd_prefix *new;
	char ip6buf[INET6_ADDRSTRLEN];
	int error;

	new = malloc(sizeof(*new), M_IP6NDP, M_NOWAIT | M_ZERO);
	if (new == NULL)
		return (ENOMEM);
	refcount_init(&new->ndpr_refcnt, newp != NULL ? 2 : 1);
	new->ndpr_ifp = pr->ndpr_ifp;
	new->ndpr_prefix = pr->ndpr_prefix;
	new->ndpr_plen = pr->ndpr_plen;
	new->ndpr_vltime = pr->ndpr_vltime;
	new->ndpr_pltime = pr->ndpr_pltime;
	new->ndpr_flags = pr->ndpr_flags;
	if ((error = in6_init_prefix_ltimes(new)) != 0) {
		free(new, M_IP6NDP);
		return (error);
	}
	new->ndpr_lastupdate = time_uptime;

	/* initialization */
	LIST_INIT(&new->ndpr_advrtrs);
	in6_prefixlen2mask(&new->ndpr_mask, new->ndpr_plen);
	/* make prefix in the canonical form */
	IN6_MASK_ADDR(&new->ndpr_prefix.sin6_addr, &new->ndpr_mask);

	ND6_WLOCK();
	LIST_INSERT_HEAD(&V_nd_prefix, new, ndpr_entry);
	V_nd6_list_genid++;
	ND6_WUNLOCK();

	/* ND_OPT_PI_FLAG_ONLINK processing */
	if (new->ndpr_raf_onlink) {
		struct epoch_tracker et;

		ND6_ONLINK_LOCK();
		NET_EPOCH_ENTER(et);
		if ((error = nd6_prefix_onlink(new)) != 0) {
			nd6log((LOG_ERR, "nd6_prelist_add: failed to make "
			    "the prefix %s/%d on-link on %s (errno=%d)\n",
			    ip6_sprintf(ip6buf, &pr->ndpr_prefix.sin6_addr),
			    pr->ndpr_plen, if_name(pr->ndpr_ifp), error));
			/* proceed anyway. XXX: is it correct? */
		}
		NET_EPOCH_EXIT(et);
		ND6_ONLINK_UNLOCK();
	}

	if (dr != NULL)
		pfxrtr_add(new, dr);
	if (newp != NULL)
		*newp = new;
	return (0);
}