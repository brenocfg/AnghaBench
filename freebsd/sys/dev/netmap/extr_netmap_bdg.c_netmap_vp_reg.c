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
struct netmap_vp_adapter {scalar_t__ na_bdg; } ;
struct netmap_adapter {scalar_t__ active_fds; int /*<<< orphan*/  na_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDG_WLOCK (scalar_t__) ; 
 int /*<<< orphan*/  BDG_WUNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  NAF_NETMAP_ON ; 
 int /*<<< orphan*/  netmap_krings_mode_commit (struct netmap_adapter*,int) ; 

int
netmap_vp_reg(struct netmap_adapter *na, int onoff)
{
	struct netmap_vp_adapter *vpna =
		(struct netmap_vp_adapter*)na;

	/* persistent ports may be put in netmap mode
	 * before being attached to a bridge
	 */
	if (vpna->na_bdg)
		BDG_WLOCK(vpna->na_bdg);
	if (onoff) {
		netmap_krings_mode_commit(na, onoff);
		if (na->active_fds == 0)
			na->na_flags |= NAF_NETMAP_ON;
		 /* XXX on FreeBSD, persistent VALE ports should also
		 * toggle IFCAP_NETMAP in na->ifp (2014-03-16)
		 */
	} else {
		if (na->active_fds == 0)
			na->na_flags &= ~NAF_NETMAP_ON;
		netmap_krings_mode_commit(na, onoff);
	}
	if (vpna->na_bdg)
		BDG_WUNLOCK(vpna->na_bdg);
	return 0;
}