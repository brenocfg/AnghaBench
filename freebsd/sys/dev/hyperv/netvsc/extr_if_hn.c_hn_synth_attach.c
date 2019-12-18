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
typedef  scalar_t__ uint32_t ;
struct ndis_rssprm_toeplitz {scalar_t__* rss_ind; int /*<<< orphan*/  rss_key; } ;
struct hn_softc {int hn_flags; scalar_t__ hn_caps; int hn_rx_ring_cnt; int hn_xvf_flags; int /*<<< orphan*/  hn_prichan; scalar_t__ hn_rss_hcap; scalar_t__ hn_rss_hash; int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_dev; scalar_t__ hn_rss_ind_size; struct ndis_rssprm_toeplitz hn_rss; } ;

/* Variables and functions */
 scalar_t__ ATTACHED_NVS ; 
 scalar_t__ ATTACHED_RNDIS ; 
 int ENXIO ; 
 int HN_FLAG_HAS_RSSIND ; 
 int HN_FLAG_HAS_RSSKEY ; 
 int HN_FLAG_RXVF ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NDIS_HASH_INDCNT ; 
 int /*<<< orphan*/  NDIS_RSS_FLAG_NONE ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int hn_attach_subchans (struct hn_softc*) ; 
 int hn_chan_attach (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_chan_detach (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int hn_nvs_attach (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_nvs_detach (struct hn_softc*) ; 
 int hn_rndis_attach (struct hn_softc*,int,int*) ; 
 int hn_rndis_conf_rss (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_rndis_detach (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_rndis_init_fixat (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_rss_ind_fixup (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_rss_key_default ; 
 int /*<<< orphan*/  hn_set_ring_inuse (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_set_txagg (struct hn_softc*) ; 
 int hn_synth_alloc_subchans (struct hn_softc*,int*) ; 
 int /*<<< orphan*/  hn_synth_attachable (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_synth_detach (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_vf_rss_fixup (struct hn_softc*,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rss_get_indirection_to_bucket (int) ; 
 int /*<<< orphan*/  rss_getkey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_synth_attach(struct hn_softc *sc, int mtu)
{
#define ATTACHED_NVS		0x0002
#define ATTACHED_RNDIS		0x0004

	struct ndis_rssprm_toeplitz *rss = &sc->hn_rss;
	int error, nsubch, nchan = 1, i, rndis_inited;
	uint32_t old_caps, attached = 0;

	KASSERT((sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) == 0,
	    ("synthetic parts were attached"));

	if (!hn_synth_attachable(sc))
		return (ENXIO);

	/* Save capabilities for later verification. */
	old_caps = sc->hn_caps;
	sc->hn_caps = 0;

	/* Clear RSS stuffs. */
	sc->hn_rss_ind_size = 0;
	sc->hn_rss_hash = 0;
	sc->hn_rss_hcap = 0;

	/*
	 * Attach the primary channel _before_ attaching NVS and RNDIS.
	 */
	error = hn_chan_attach(sc, sc->hn_prichan);
	if (error)
		goto failed;

	/*
	 * Attach NVS.
	 */
	error = hn_nvs_attach(sc, mtu);
	if (error)
		goto failed;
	attached |= ATTACHED_NVS;

	/*
	 * Attach RNDIS _after_ NVS is attached.
	 */
	error = hn_rndis_attach(sc, mtu, &rndis_inited);
	if (rndis_inited)
		attached |= ATTACHED_RNDIS;
	if (error)
		goto failed;

	/*
	 * Make sure capabilities are not changed.
	 */
	if (device_is_attached(sc->hn_dev) && old_caps != sc->hn_caps) {
		if_printf(sc->hn_ifp, "caps mismatch old 0x%08x, new 0x%08x\n",
		    old_caps, sc->hn_caps);
		error = ENXIO;
		goto failed;
	}

	/*
	 * Allocate sub-channels for multi-TX/RX rings.
	 *
	 * NOTE:
	 * The # of RX rings that can be used is equivalent to the # of
	 * channels to be requested.
	 */
	nsubch = sc->hn_rx_ring_cnt - 1;
	error = hn_synth_alloc_subchans(sc, &nsubch);
	if (error)
		goto failed;
	/* NOTE: _Full_ synthetic parts detach is required now. */
	sc->hn_flags |= HN_FLAG_SYNTH_ATTACHED;

	/*
	 * Set the # of TX/RX rings that could be used according to
	 * the # of channels that NVS offered.
	 */
	nchan = nsubch + 1;
	hn_set_ring_inuse(sc, nchan);
	if (nchan == 1) {
		/* Only the primary channel can be used; done */
		goto back;
	}

	/*
	 * Attach the sub-channels.
	 *
	 * NOTE: hn_set_ring_inuse() _must_ have been called.
	 */
	error = hn_attach_subchans(sc);
	if (error)
		goto failed;

	/*
	 * Configure RSS key and indirect table _after_ all sub-channels
	 * are attached.
	 */
	if ((sc->hn_flags & HN_FLAG_HAS_RSSKEY) == 0) {
		/*
		 * RSS key is not set yet; set it to the default RSS key.
		 */
		if (bootverbose)
			if_printf(sc->hn_ifp, "setup default RSS key\n");
#ifdef RSS
		rss_getkey(rss->rss_key);
#else
		memcpy(rss->rss_key, hn_rss_key_default, sizeof(rss->rss_key));
#endif
		sc->hn_flags |= HN_FLAG_HAS_RSSKEY;
	}

	if ((sc->hn_flags & HN_FLAG_HAS_RSSIND) == 0) {
		/*
		 * RSS indirect table is not set yet; set it up in round-
		 * robin fashion.
		 */
		if (bootverbose) {
			if_printf(sc->hn_ifp, "setup default RSS indirect "
			    "table\n");
		}
		for (i = 0; i < NDIS_HASH_INDCNT; ++i) {
			uint32_t subidx;

#ifdef RSS
			subidx = rss_get_indirection_to_bucket(i);
#else
			subidx = i;
#endif
			rss->rss_ind[i] = subidx % nchan;
		}
		sc->hn_flags |= HN_FLAG_HAS_RSSIND;
	} else {
		/*
		 * # of usable channels may be changed, so we have to
		 * make sure that all entries in RSS indirect table
		 * are valid.
		 *
		 * NOTE: hn_set_ring_inuse() _must_ have been called.
		 */
		hn_rss_ind_fixup(sc);
	}

	sc->hn_rss_hash = sc->hn_rss_hcap;
	if ((sc->hn_flags & HN_FLAG_RXVF) ||
	    (sc->hn_xvf_flags & HN_XVFFLAG_ENABLED)) {
		/* NOTE: Don't reconfigure RSS; will do immediately. */
		hn_vf_rss_fixup(sc, false);
	}
	error = hn_rndis_conf_rss(sc, NDIS_RSS_FLAG_NONE);
	if (error)
		goto failed;
back:
	/*
	 * Fixup transmission aggregation setup.
	 */
	hn_set_txagg(sc);
	hn_rndis_init_fixat(sc, nchan);
	return (0);

failed:
	if (sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) {
		hn_rndis_init_fixat(sc, nchan);
		hn_synth_detach(sc);
	} else {
		if (attached & ATTACHED_RNDIS) {
			hn_rndis_init_fixat(sc, nchan);
			hn_rndis_detach(sc);
		}
		if (attached & ATTACHED_NVS)
			hn_nvs_detach(sc);
		hn_chan_detach(sc, sc->hn_prichan);
		/* Restore old capabilities. */
		sc->hn_caps = old_caps;
	}
	return (error);

#undef ATTACHED_RNDIS
#undef ATTACHED_NVS
}