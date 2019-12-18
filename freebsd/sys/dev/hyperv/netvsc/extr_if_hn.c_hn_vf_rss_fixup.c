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
typedef  int uint32_t ;
struct ifrsskey {int ifrh_types; int /*<<< orphan*/  ifrk_key; int /*<<< orphan*/  ifrh_func; int /*<<< orphan*/  ifrh_name; int /*<<< orphan*/  ifrk_keylen; int /*<<< orphan*/  ifrk_func; int /*<<< orphan*/  ifrk_name; } ;
struct ifrsshash {int ifrh_types; int /*<<< orphan*/  ifrk_key; int /*<<< orphan*/  ifrh_func; int /*<<< orphan*/  ifrh_name; int /*<<< orphan*/  ifrk_keylen; int /*<<< orphan*/  ifrk_func; int /*<<< orphan*/  ifrk_name; } ;
struct ifnet {int (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_xname; } ;
struct TYPE_2__ {int /*<<< orphan*/  rss_key; } ;
struct hn_softc {int hn_flags; int hn_rx_ring_inuse; int hn_rss_hcap; int hn_rss_hash; TYPE_1__ hn_rss; struct ifnet* hn_vf_ifp; struct ifnet* hn_ifp; } ;
typedef  int /*<<< orphan*/  ifrk ;
typedef  int /*<<< orphan*/  ifrh ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int HN_FLAG_HAS_RSSKEY ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NDIS_HASH_FUNCTION_MASK ; 
 int NDIS_HASH_FUNCTION_TOEPLITZ ; 
 int /*<<< orphan*/  NDIS_HASH_KEYSIZE_TOEPLITZ ; 
 int /*<<< orphan*/  RSS_FUNC_TOEPLITZ ; 
 int RSS_TYPE_IPV4 ; 
 int RSS_TYPE_IPV6 ; 
 int RSS_TYPE_IPV6_EX ; 
 int RSS_TYPE_TCP_IPV4 ; 
 int RSS_TYPE_TCP_IPV6 ; 
 int RSS_TYPE_TCP_IPV6_EX ; 
 int RSS_TYPE_UDP_IPV4 ; 
 int RSS_TYPE_UDP_IPV6 ; 
 int RSS_TYPE_UDP_IPV6_EX ; 
 int /*<<< orphan*/  SIOCGIFRSSHASH ; 
 int /*<<< orphan*/  SIOCGIFRSSKEY ; 
 int /*<<< orphan*/  hn_rss_mbuf_hash (struct hn_softc*,int) ; 
 int hn_rss_reconfig (struct hn_softc*) ; 
 int hn_rss_type_fromndis (int) ; 
 int hn_rss_type_tondis (int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ifrsskey*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_vf_rss_fixup(struct hn_softc *sc, bool reconf)
{
	struct ifnet *ifp, *vf_ifp;
	struct ifrsshash ifrh;
	struct ifrsskey ifrk;
	int error;
	uint32_t my_types, diff_types, mbuf_types = 0;

	HN_LOCK_ASSERT(sc);
	KASSERT(sc->hn_flags & HN_FLAG_SYNTH_ATTACHED,
	    ("%s: synthetic parts are not attached", sc->hn_ifp->if_xname));

	if (sc->hn_rx_ring_inuse == 1) {
		/* No RSS on synthetic parts; done. */
		return;
	}
	if ((sc->hn_rss_hcap & NDIS_HASH_FUNCTION_TOEPLITZ) == 0) {
		/* Synthetic parts do not support Toeplitz; done. */
		return;
	}

	ifp = sc->hn_ifp;
	vf_ifp = sc->hn_vf_ifp;

	/*
	 * Extract VF's RSS key.  Only 40 bytes key for Toeplitz is
	 * supported.
	 */
	memset(&ifrk, 0, sizeof(ifrk));
	strlcpy(ifrk.ifrk_name, vf_ifp->if_xname, sizeof(ifrk.ifrk_name));
	error = vf_ifp->if_ioctl(vf_ifp, SIOCGIFRSSKEY, (caddr_t)&ifrk);
	if (error) {
		if_printf(ifp, "%s SIOCGRSSKEY failed: %d\n",
		    vf_ifp->if_xname, error);
		goto done;
	}
	if (ifrk.ifrk_func != RSS_FUNC_TOEPLITZ) {
		if_printf(ifp, "%s RSS function %u is not Toeplitz\n",
		    vf_ifp->if_xname, ifrk.ifrk_func);
		goto done;
	}
	if (ifrk.ifrk_keylen != NDIS_HASH_KEYSIZE_TOEPLITZ) {
		if_printf(ifp, "%s invalid RSS Toeplitz key length %d\n",
		    vf_ifp->if_xname, ifrk.ifrk_keylen);
		goto done;
	}

	/*
	 * Extract VF's RSS hash.  Only Toeplitz is supported.
	 */
	memset(&ifrh, 0, sizeof(ifrh));
	strlcpy(ifrh.ifrh_name, vf_ifp->if_xname, sizeof(ifrh.ifrh_name));
	error = vf_ifp->if_ioctl(vf_ifp, SIOCGIFRSSHASH, (caddr_t)&ifrh);
	if (error) {
		if_printf(ifp, "%s SIOCGRSSHASH failed: %d\n",
		    vf_ifp->if_xname, error);
		goto done;
	}
	if (ifrh.ifrh_func != RSS_FUNC_TOEPLITZ) {
		if_printf(ifp, "%s RSS function %u is not Toeplitz\n",
		    vf_ifp->if_xname, ifrh.ifrh_func);
		goto done;
	}

	my_types = hn_rss_type_fromndis(sc->hn_rss_hcap);
	if ((ifrh.ifrh_types & my_types) == 0) {
		/* This disables RSS; ignore it then */
		if_printf(ifp, "%s intersection of RSS types failed.  "
		    "VF %#x, mine %#x\n", vf_ifp->if_xname,
		    ifrh.ifrh_types, my_types);
		goto done;
	}

	diff_types = my_types ^ ifrh.ifrh_types;
	my_types &= ifrh.ifrh_types;
	mbuf_types = my_types;

	/*
	 * Detect RSS hash value/type confliction.
	 *
	 * NOTE:
	 * We don't disable the hash type, but stop delivery the hash
	 * value/type through mbufs on RX path.
	 *
	 * XXX If HN_CAP_UDPHASH is set in hn_caps, then UDP 4-tuple
	 * hash is delivered with type of TCP_IPV4.  This means if
	 * UDP_IPV4 is enabled, then TCP_IPV4 should be forced, at
	 * least to hn_mbuf_hash.  However, given that _all_ of the
	 * NICs implement TCP_IPV4, this will _not_ impose any issues
	 * here.
	 */
	if ((my_types & RSS_TYPE_IPV4) &&
	    (diff_types & ifrh.ifrh_types &
	     (RSS_TYPE_TCP_IPV4 | RSS_TYPE_UDP_IPV4))) {
		/* Conflict; disable IPV4 hash type/value delivery. */
		if_printf(ifp, "disable IPV4 mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_IPV4;
	}
	if ((my_types & RSS_TYPE_IPV6) &&
	    (diff_types & ifrh.ifrh_types &
	     (RSS_TYPE_TCP_IPV6 | RSS_TYPE_UDP_IPV6 |
	      RSS_TYPE_TCP_IPV6_EX | RSS_TYPE_UDP_IPV6_EX |
	      RSS_TYPE_IPV6_EX))) {
		/* Conflict; disable IPV6 hash type/value delivery. */
		if_printf(ifp, "disable IPV6 mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_IPV6;
	}
	if ((my_types & RSS_TYPE_IPV6_EX) &&
	    (diff_types & ifrh.ifrh_types &
	     (RSS_TYPE_TCP_IPV6 | RSS_TYPE_UDP_IPV6 |
	      RSS_TYPE_TCP_IPV6_EX | RSS_TYPE_UDP_IPV6_EX |
	      RSS_TYPE_IPV6))) {
		/* Conflict; disable IPV6_EX hash type/value delivery. */
		if_printf(ifp, "disable IPV6_EX mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_IPV6_EX;
	}
	if ((my_types & RSS_TYPE_TCP_IPV6) &&
	    (diff_types & ifrh.ifrh_types & RSS_TYPE_TCP_IPV6_EX)) {
		/* Conflict; disable TCP_IPV6 hash type/value delivery. */
		if_printf(ifp, "disable TCP_IPV6 mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_TCP_IPV6;
	}
	if ((my_types & RSS_TYPE_TCP_IPV6_EX) &&
	    (diff_types & ifrh.ifrh_types & RSS_TYPE_TCP_IPV6)) {
		/* Conflict; disable TCP_IPV6_EX hash type/value delivery. */
		if_printf(ifp, "disable TCP_IPV6_EX mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_TCP_IPV6_EX;
	}
	if ((my_types & RSS_TYPE_UDP_IPV6) &&
	    (diff_types & ifrh.ifrh_types & RSS_TYPE_UDP_IPV6_EX)) {
		/* Conflict; disable UDP_IPV6 hash type/value delivery. */
		if_printf(ifp, "disable UDP_IPV6 mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_UDP_IPV6;
	}
	if ((my_types & RSS_TYPE_UDP_IPV6_EX) &&
	    (diff_types & ifrh.ifrh_types & RSS_TYPE_UDP_IPV6)) {
		/* Conflict; disable UDP_IPV6_EX hash type/value delivery. */
		if_printf(ifp, "disable UDP_IPV6_EX mbuf hash delivery\n");
		mbuf_types &= ~RSS_TYPE_UDP_IPV6_EX;
	}

	/*
	 * Indirect table does not matter.
	 */

	sc->hn_rss_hash = (sc->hn_rss_hcap & NDIS_HASH_FUNCTION_MASK) |
	    hn_rss_type_tondis(my_types);
	memcpy(sc->hn_rss.rss_key, ifrk.ifrk_key, sizeof(sc->hn_rss.rss_key));
	sc->hn_flags |= HN_FLAG_HAS_RSSKEY;

	if (reconf) {
		error = hn_rss_reconfig(sc);
		if (error) {
			/* XXX roll-back? */
			if_printf(ifp, "hn_rss_reconfig failed: %d\n", error);
			/* XXX keep going. */
		}
	}
done:
	/* Hash deliverability for mbufs. */
	hn_rss_mbuf_hash(sc, hn_rss_type_tondis(mbuf_types));
}