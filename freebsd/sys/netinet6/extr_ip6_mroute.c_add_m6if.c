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
struct mif6ctl {scalar_t__ mif6c_mifi; scalar_t__ mif6c_pifi; int mif6c_flags; } ;
struct mif6 {int m6_flags; scalar_t__ m6_bytes_out; scalar_t__ m6_bytes_in; scalar_t__ m6_pkt_out; scalar_t__ m6_pkt_in; struct ifnet* m6_ifp; } ;
struct ifnet {int if_flags; scalar_t__ if_index; } ;
typedef  scalar_t__ mifi_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ANY ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFT_OTHER ; 
 scalar_t__ MAXMIFS ; 
 int /*<<< orphan*/  MIF6_LOCK () ; 
 int /*<<< orphan*/  MIF6_UNLOCK () ; 
 int MIFF_REGISTER ; 
 int /*<<< orphan*/  MRT6_DLOG (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ V_if_index ; 
 int if_allmulti (struct ifnet*,int) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 struct ifnet* ifnet_byindex (scalar_t__) ; 
 struct mif6* mif6table ; 
 struct ifnet* multicast_register_if6 ; 
 scalar_t__ nummifs ; 
 scalar_t__ reg_mif_num ; 

__attribute__((used)) static int
add_m6if(struct mif6ctl *mifcp)
{
	struct mif6 *mifp;
	struct ifnet *ifp;
	int error;

	MIF6_LOCK();

	if (mifcp->mif6c_mifi >= MAXMIFS) {
		MIF6_UNLOCK();
		return (EINVAL);
	}
	mifp = mif6table + mifcp->mif6c_mifi;
	if (mifp->m6_ifp != NULL) {
		MIF6_UNLOCK();
		return (EADDRINUSE); /* XXX: is it appropriate? */
	}
	if (mifcp->mif6c_pifi == 0 || mifcp->mif6c_pifi > V_if_index) {
		MIF6_UNLOCK();
		return (ENXIO);
	}

	ifp = ifnet_byindex(mifcp->mif6c_pifi);

	if (mifcp->mif6c_flags & MIFF_REGISTER) {
		if (reg_mif_num == (mifi_t)-1) {
			ifp = if_alloc(IFT_OTHER);

			if_initname(ifp, "register_mif", 0);
			ifp->if_flags |= IFF_LOOPBACK;
			if_attach(ifp);
			multicast_register_if6 = ifp;
			reg_mif_num = mifcp->mif6c_mifi;
			/*
			 * it is impossible to guess the ifindex of the
			 * register interface.  So mif6c_pifi is automatically
			 * calculated.
			 */
			mifcp->mif6c_pifi = ifp->if_index;
		} else {
			ifp = multicast_register_if6;
		}
	} else {
		/* Make sure the interface supports multicast */
		if ((ifp->if_flags & IFF_MULTICAST) == 0) {
			MIF6_UNLOCK();
			return (EOPNOTSUPP);
		}

		error = if_allmulti(ifp, 1);
		if (error) {
			MIF6_UNLOCK();
			return (error);
		}
	}

	mifp->m6_flags     = mifcp->mif6c_flags;
	mifp->m6_ifp       = ifp;

	/* initialize per mif pkt counters */
	mifp->m6_pkt_in    = 0;
	mifp->m6_pkt_out   = 0;
	mifp->m6_bytes_in  = 0;
	mifp->m6_bytes_out = 0;

	/* Adjust nummifs up if the mifi is higher than nummifs */
	if (nummifs <= mifcp->mif6c_mifi)
		nummifs = mifcp->mif6c_mifi + 1;

	MIF6_UNLOCK();
	MRT6_DLOG(DEBUG_ANY, "mif #%d, phyint %s", mifcp->mif6c_mifi,
	    if_name(ifp));

	return (0);
}