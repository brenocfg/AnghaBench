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
struct mif6 {int m6_flags; struct ifnet* m6_ifp; } ;
struct ifnet {int dummy; } ;
typedef  int mifi_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ANY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MIF6_LOCK_ASSERT () ; 
 int MIFF_REGISTER ; 
 int /*<<< orphan*/  MRT6_DLOG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_allmulti (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 struct mif6* mif6table ; 
 int /*<<< orphan*/ * multicast_register_if6 ; 
 int nummifs ; 
 int reg_mif_num ; 

__attribute__((used)) static int
del_m6if_locked(mifi_t *mifip)
{
	struct mif6 *mifp = mif6table + *mifip;
	mifi_t mifi;
	struct ifnet *ifp;

	MIF6_LOCK_ASSERT();

	if (*mifip >= nummifs)
		return (EINVAL);
	if (mifp->m6_ifp == NULL)
		return (EINVAL);

	if (!(mifp->m6_flags & MIFF_REGISTER)) {
		/* XXX: TODO: Maintain an ALLMULTI refcount in struct ifnet. */
		ifp = mifp->m6_ifp;
		if_allmulti(ifp, 0);
	} else {
		if (reg_mif_num != (mifi_t)-1 &&
		    multicast_register_if6 != NULL) {
			if_detach(multicast_register_if6);
			if_free(multicast_register_if6);
			reg_mif_num = (mifi_t)-1;
			multicast_register_if6 = NULL;
		}
	}

	bzero((caddr_t)mifp, sizeof(*mifp));

	/* Adjust nummifs down */
	for (mifi = nummifs; mifi > 0; mifi--)
		if (mif6table[mifi - 1].m6_ifp)
			break;
	nummifs = mifi;
	MRT6_DLOG(DEBUG_ANY, "mif %d, nummifs %d", *mifip, nummifs);

	return (0);
}