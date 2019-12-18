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
struct TYPE_2__ {scalar_t__ ndis_type; scalar_t__ ndis_rev; size_t ndis_size; } ;
struct ndis_rss_caps {int ndis_nrxr; int ndis_nind; int ndis_caps; TYPE_1__ ndis_hdr; } ;
struct hn_softc {scalar_t__ hn_ndis_ver; int hn_rss_ind_size; int hn_rss_hcap; int hn_caps; int /*<<< orphan*/  hn_ifp; } ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int HN_CAP_UDPHASH ; 
 scalar_t__ HN_NDIS_VERSION_6_20 ; 
 int NDIS_HASH_INDCNT ; 
 int NDIS_HASH_IPV4 ; 
 int NDIS_HASH_IPV6 ; 
 int NDIS_HASH_IPV6_EX ; 
 int NDIS_HASH_TCP_IPV4 ; 
 int NDIS_HASH_TCP_IPV6 ; 
 int NDIS_HASH_TCP_IPV6_EX ; 
 int NDIS_HASH_UDP_IPV4_X ; 
 scalar_t__ NDIS_OBJTYPE_RSS_CAPS ; 
 scalar_t__ NDIS_RSS_CAPS_REV_1 ; 
 scalar_t__ NDIS_RSS_CAPS_REV_2 ; 
 void* NDIS_RSS_CAPS_SIZE ; 
 size_t NDIS_RSS_CAPS_SIZE_6_0 ; 
 int NDIS_RSS_CAP_HASHFUNC_MASK ; 
 int NDIS_RSS_CAP_IPV4 ; 
 int NDIS_RSS_CAP_IPV6 ; 
 int NDIS_RSS_CAP_IPV6_EX ; 
 int /*<<< orphan*/  OID_GEN_RECEIVE_SCALE_CAPABILITIES ; 
 scalar_t__ bootverbose ; 
 int ffs (int) ; 
 int hn_rndis_query2 (struct hn_softc*,int /*<<< orphan*/ ,struct ndis_rss_caps*,void*,struct ndis_rss_caps*,size_t*,size_t) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct ndis_rss_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 

int
hn_rndis_query_rsscaps(struct hn_softc *sc, int *rxr_cnt0)
{
	struct ndis_rss_caps in, caps;
	size_t caps_len;
	int error, indsz, rxr_cnt, hash_fnidx;
	uint32_t hash_func = 0, hash_types = 0;

	*rxr_cnt0 = 0;

	if (sc->hn_ndis_ver < HN_NDIS_VERSION_6_20)
		return (EOPNOTSUPP);

	memset(&in, 0, sizeof(in));
	in.ndis_hdr.ndis_type = NDIS_OBJTYPE_RSS_CAPS;
	in.ndis_hdr.ndis_rev = NDIS_RSS_CAPS_REV_2;
	in.ndis_hdr.ndis_size = NDIS_RSS_CAPS_SIZE;

	caps_len = NDIS_RSS_CAPS_SIZE;
	error = hn_rndis_query2(sc, OID_GEN_RECEIVE_SCALE_CAPABILITIES,
	    &in, NDIS_RSS_CAPS_SIZE, &caps, &caps_len, NDIS_RSS_CAPS_SIZE_6_0);
	if (error)
		return (error);

	/*
	 * Preliminary verification.
	 */
	if (caps.ndis_hdr.ndis_type != NDIS_OBJTYPE_RSS_CAPS) {
		if_printf(sc->hn_ifp, "invalid NDIS objtype 0x%02x\n",
		    caps.ndis_hdr.ndis_type);
		return (EINVAL);
	}
	if (caps.ndis_hdr.ndis_rev < NDIS_RSS_CAPS_REV_1) {
		if_printf(sc->hn_ifp, "invalid NDIS objrev 0x%02x\n",
		    caps.ndis_hdr.ndis_rev);
		return (EINVAL);
	}
	if (caps.ndis_hdr.ndis_size > caps_len) {
		if_printf(sc->hn_ifp, "invalid NDIS objsize %u, "
		    "data size %zu\n", caps.ndis_hdr.ndis_size, caps_len);
		return (EINVAL);
	} else if (caps.ndis_hdr.ndis_size < NDIS_RSS_CAPS_SIZE_6_0) {
		if_printf(sc->hn_ifp, "invalid NDIS objsize %u\n",
		    caps.ndis_hdr.ndis_size);
		return (EINVAL);
	}

	/*
	 * Save information for later RSS configuration.
	 */
	if (caps.ndis_nrxr == 0) {
		if_printf(sc->hn_ifp, "0 RX rings!?\n");
		return (EINVAL);
	}
	if (bootverbose)
		if_printf(sc->hn_ifp, "%u RX rings\n", caps.ndis_nrxr);
	rxr_cnt = caps.ndis_nrxr;

	if (caps.ndis_hdr.ndis_size == NDIS_RSS_CAPS_SIZE &&
	    caps.ndis_hdr.ndis_rev >= NDIS_RSS_CAPS_REV_2) {
		if (caps.ndis_nind > NDIS_HASH_INDCNT) {
			if_printf(sc->hn_ifp,
			    "too many RSS indirect table entries %u\n",
			    caps.ndis_nind);
			return (EOPNOTSUPP);
		}
		if (!powerof2(caps.ndis_nind)) {
			if_printf(sc->hn_ifp, "RSS indirect table size is not "
			    "power-of-2 %u\n", caps.ndis_nind);
		}

		if (bootverbose) {
			if_printf(sc->hn_ifp, "RSS indirect table size %u\n",
			    caps.ndis_nind);
		}
		indsz = caps.ndis_nind;
	} else {
		indsz = NDIS_HASH_INDCNT;
	}
	if (indsz < rxr_cnt) {
		if_printf(sc->hn_ifp, "# of RX rings (%d) > "
		    "RSS indirect table size %d\n", rxr_cnt, indsz);
		rxr_cnt = indsz;
	}

	/*
	 * NOTE:
	 * Toeplitz is at the lowest bit, and it is prefered; so ffs(),
	 * instead of fls(), is used here.
	 */
	hash_fnidx = ffs(caps.ndis_caps & NDIS_RSS_CAP_HASHFUNC_MASK);
	if (hash_fnidx == 0) {
		if_printf(sc->hn_ifp, "no hash functions, caps 0x%08x\n",
		    caps.ndis_caps);
		return (EOPNOTSUPP);
	}
	hash_func = 1 << (hash_fnidx - 1); /* ffs is 1-based */

	if (caps.ndis_caps & NDIS_RSS_CAP_IPV4)
		hash_types |= NDIS_HASH_IPV4 | NDIS_HASH_TCP_IPV4;
	if (caps.ndis_caps & NDIS_RSS_CAP_IPV6)
		hash_types |= NDIS_HASH_IPV6 | NDIS_HASH_TCP_IPV6;
	if (caps.ndis_caps & NDIS_RSS_CAP_IPV6_EX)
		hash_types |= NDIS_HASH_IPV6_EX | NDIS_HASH_TCP_IPV6_EX;
	if (hash_types == 0) {
		if_printf(sc->hn_ifp, "no hash types, caps 0x%08x\n",
		    caps.ndis_caps);
		return (EOPNOTSUPP);
	}
	if (bootverbose)
		if_printf(sc->hn_ifp, "RSS caps %#x\n", caps.ndis_caps);

	/* Commit! */
	sc->hn_rss_ind_size = indsz;
	sc->hn_rss_hcap = hash_func | hash_types;
	if (sc->hn_caps & HN_CAP_UDPHASH) {
		/* UDP 4-tuple hash is unconditionally enabled. */
		sc->hn_rss_hcap |= NDIS_HASH_UDP_IPV4_X;
	}
	*rxr_cnt0 = rxr_cnt;
	return (0);
}