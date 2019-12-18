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
typedef  int u_int ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct lltable {struct ifnet* llt_ifp; } ;
struct llentry {int la_flags; int r_flags; int /*<<< orphan*/  lle_epoch_ctx; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LLE_IFADDR ; 
 int LLE_MAX_LINKHDR ; 
 int LLE_STATIC ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int RLLE_IFADDR ; 
 int RLLE_VALID ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_lltable_destroy_lle_unlocked ; 
 struct llentry* in_lltable_new (int /*<<< orphan*/ ,int) ; 
 scalar_t__ in_lltable_rtcheck (struct ifnet*,int,struct sockaddr const*) ; 
 scalar_t__ lltable_calc_llheader (struct ifnet*,scalar_t__,int /*<<< orphan*/ ,char*,size_t*,int*) ; 
 int /*<<< orphan*/  lltable_set_entry_addr (struct ifnet*,struct llentry*,char*,size_t,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  net_epoch_preempt ; 

__attribute__((used)) static struct llentry *
in_lltable_alloc(struct lltable *llt, u_int flags, const struct sockaddr *l3addr)
{
	const struct sockaddr_in *sin = (const struct sockaddr_in *)l3addr;
	struct ifnet *ifp = llt->llt_ifp;
	struct llentry *lle;
	char linkhdr[LLE_MAX_LINKHDR];
	size_t linkhdrsize;
	int lladdr_off;

	KASSERT(l3addr->sa_family == AF_INET,
	    ("sin_family %d", l3addr->sa_family));

	/*
	 * A route that covers the given address must have
	 * been installed 1st because we are doing a resolution,
	 * verify this.
	 */
	if (!(flags & LLE_IFADDR) &&
	    in_lltable_rtcheck(ifp, flags, l3addr) != 0)
		return (NULL);

	lle = in_lltable_new(sin->sin_addr, flags);
	if (lle == NULL) {
		log(LOG_INFO, "lla_lookup: new lle malloc failed\n");
		return (NULL);
	}
	lle->la_flags = flags;
	if (flags & LLE_STATIC)
		lle->r_flags |= RLLE_VALID;
	if ((flags & LLE_IFADDR) == LLE_IFADDR) {
		linkhdrsize = LLE_MAX_LINKHDR;
		if (lltable_calc_llheader(ifp, AF_INET, IF_LLADDR(ifp),
		    linkhdr, &linkhdrsize, &lladdr_off) != 0) {
			epoch_call(net_epoch_preempt,  &lle->lle_epoch_ctx, in_lltable_destroy_lle_unlocked);
			return (NULL);
		}
		lltable_set_entry_addr(ifp, lle, linkhdr, linkhdrsize,
		    lladdr_off);
		lle->la_flags |= LLE_STATIC;
		lle->r_flags |= (RLLE_VALID | RLLE_IFADDR);
	}

	return (lle);
}