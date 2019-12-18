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
typedef  scalar_t__ u_int ;
struct ifnet {int if_capabilities; scalar_t__ if_hw_tsomax; } ;
struct hn_softc {int hn_ndis_tso_sgmin; int hn_ndis_tso_szmax; TYPE_1__* hn_vf_ifp; struct ifnet* hn_ifp; } ;
struct TYPE_2__ {scalar_t__ if_hw_tsomax; } ;

/* Variables and functions */
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IP_MAXPACKET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ hn_xpnt_vf_isready (struct hn_softc*) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,scalar_t__) ; 

__attribute__((used)) static void
hn_set_tso_maxsize(struct hn_softc *sc, int tso_maxlen, int mtu)
{
	struct ifnet *ifp = sc->hn_ifp;
	u_int hw_tsomax;
	int tso_minlen;

	HN_LOCK_ASSERT(sc);

	if ((ifp->if_capabilities & (IFCAP_TSO4 | IFCAP_TSO6)) == 0)
		return;

	KASSERT(sc->hn_ndis_tso_sgmin >= 2,
	    ("invalid NDIS tso sgmin %d", sc->hn_ndis_tso_sgmin));
	tso_minlen = sc->hn_ndis_tso_sgmin * mtu;

	KASSERT(sc->hn_ndis_tso_szmax >= tso_minlen &&
	    sc->hn_ndis_tso_szmax <= IP_MAXPACKET,
	    ("invalid NDIS tso szmax %d", sc->hn_ndis_tso_szmax));

	if (tso_maxlen < tso_minlen)
		tso_maxlen = tso_minlen;
	else if (tso_maxlen > IP_MAXPACKET)
		tso_maxlen = IP_MAXPACKET;
	if (tso_maxlen > sc->hn_ndis_tso_szmax)
		tso_maxlen = sc->hn_ndis_tso_szmax;
	hw_tsomax = tso_maxlen - (ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN);

	if (hn_xpnt_vf_isready(sc)) {
		if (hw_tsomax > sc->hn_vf_ifp->if_hw_tsomax)
			hw_tsomax = sc->hn_vf_ifp->if_hw_tsomax;
	}
	ifp->if_hw_tsomax = hw_tsomax;
	if (bootverbose)
		if_printf(ifp, "TSO size max %u\n", ifp->if_hw_tsomax);
}