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
typedef  int /*<<< orphan*/  u_char ;
struct lltable {int /*<<< orphan*/  llt_af; } ;
struct llentry {int la_flags; int /*<<< orphan*/  r_linkdata; int /*<<< orphan*/ * ll_addr; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  linkhdr ;

/* Variables and functions */
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int LLE_IFADDR ; 
 int LLE_MAX_LINKHDR ; 
 int LLE_VALID ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  lltable_calc_llheader (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
llentry_update_ifaddr(struct lltable *llt, struct llentry *lle, void *farg)
{
	struct ifnet *ifp;
	u_char linkhdr[LLE_MAX_LINKHDR];
	size_t linkhdrsize;
	u_char *lladdr;
	int lladdr_off;

	ifp = (struct ifnet *)farg;

	lladdr = lle->ll_addr;

	LLE_WLOCK(lle);
	if ((lle->la_flags & LLE_VALID) == 0) {
		LLE_WUNLOCK(lle);
		return (0);
	}

	if ((lle->la_flags & LLE_IFADDR) != 0)
		lladdr = IF_LLADDR(ifp);

	linkhdrsize = sizeof(linkhdr);
	lltable_calc_llheader(ifp, llt->llt_af, lladdr, linkhdr, &linkhdrsize,
	    &lladdr_off);
	memcpy(lle->r_linkdata, linkhdr, linkhdrsize);
	LLE_WUNLOCK(lle);

	return (0);
}