#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {size_t ndis_size; int /*<<< orphan*/  ndis_rev; int /*<<< orphan*/  ndis_type; } ;
struct ndis_offload_params {scalar_t__ ndis_ip4csum; scalar_t__ ndis_tcp4csum; scalar_t__ ndis_udp4csum; scalar_t__ ndis_tcp6csum; scalar_t__ ndis_udp6csum; void* ndis_lsov2_ip6; void* ndis_lsov2_ip4; TYPE_1__ ndis_hdr; } ;
struct TYPE_6__ {int ndis_ip4_txcsum; int ndis_ip4_rxcsum; int ndis_ip6_txcsum; int ndis_ip6_rxcsum; } ;
struct TYPE_5__ {int ndis_ip4_encap; int ndis_ip4_maxsz; int ndis_ip4_minsg; int ndis_ip6_encap; int ndis_ip6_opts; int ndis_ip6_maxsz; int ndis_ip6_minsg; } ;
struct ndis_offload {TYPE_3__ ndis_csum; TYPE_2__ ndis_lsov2; } ;
struct hn_softc {scalar_t__ hn_ndis_ver; int hn_ndis_tso_szmax; int hn_ndis_tso_sgmin; int hn_caps; int /*<<< orphan*/  hn_ifp; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int HN_CAP_IPCS ; 
 int HN_CAP_TCP4CS ; 
 int HN_CAP_TCP6CS ; 
 int HN_CAP_TSO4 ; 
 int HN_CAP_TSO6 ; 
 int HN_CAP_UDP4CS ; 
 int HN_CAP_UDP6CS ; 
 int HN_NDIS_LSOV2_CAP_IP6 ; 
 int HN_NDIS_TXCSUM_CAP_IP4 ; 
 int HN_NDIS_TXCSUM_CAP_TCP4 ; 
 int HN_NDIS_TXCSUM_CAP_TCP6 ; 
 int HN_NDIS_TXCSUM_CAP_UDP6 ; 
 scalar_t__ HN_NDIS_VERSION_6_30 ; 
 int IP_MAXPACKET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NDIS_OBJTYPE_DEFAULT ; 
 int NDIS_OFFLOAD_ENCAP_8023 ; 
 void* NDIS_OFFLOAD_LSOV2_OFF ; 
 void* NDIS_OFFLOAD_LSOV2_ON ; 
 int /*<<< orphan*/  NDIS_OFFLOAD_PARAMS_REV_2 ; 
 int /*<<< orphan*/  NDIS_OFFLOAD_PARAMS_REV_3 ; 
 size_t NDIS_OFFLOAD_PARAMS_SIZE ; 
 size_t NDIS_OFFLOAD_PARAMS_SIZE_6_1 ; 
 void* NDIS_OFFLOAD_PARAM_RX ; 
 scalar_t__ NDIS_OFFLOAD_PARAM_TX ; 
 void* NDIS_OFFLOAD_PARAM_TXRX ; 
 int NDIS_RXCSUM_CAP_IP4 ; 
 int NDIS_RXCSUM_CAP_TCP4 ; 
 int NDIS_RXCSUM_CAP_TCP6 ; 
 int NDIS_RXCSUM_CAP_UDP4 ; 
 int NDIS_RXCSUM_CAP_UDP6 ; 
 int NDIS_TXCSUM_CAP_UDP4 ; 
 int /*<<< orphan*/  OID_TCP_OFFLOAD_PARAMETERS ; 
 scalar_t__ bootverbose ; 
 int hn_rndis_query_hwcaps (struct hn_softc*,struct ndis_offload*) ; 
 int hn_rndis_set (struct hn_softc*,int /*<<< orphan*/ ,struct ndis_offload_params*,size_t) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct ndis_offload_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hn_rndis_conf_offload(struct hn_softc *sc, int mtu)
{
	struct ndis_offload hwcaps;
	struct ndis_offload_params params;
	uint32_t caps = 0;
	size_t paramsz;
	int error, tso_maxsz, tso_minsg;

	error = hn_rndis_query_hwcaps(sc, &hwcaps);
	if (error) {
		if_printf(sc->hn_ifp, "hwcaps query failed: %d\n", error);
		return (error);
	}

	/* NOTE: 0 means "no change" */
	memset(&params, 0, sizeof(params));

	params.ndis_hdr.ndis_type = NDIS_OBJTYPE_DEFAULT;
	if (sc->hn_ndis_ver < HN_NDIS_VERSION_6_30) {
		params.ndis_hdr.ndis_rev = NDIS_OFFLOAD_PARAMS_REV_2;
		paramsz = NDIS_OFFLOAD_PARAMS_SIZE_6_1;
	} else {
		params.ndis_hdr.ndis_rev = NDIS_OFFLOAD_PARAMS_REV_3;
		paramsz = NDIS_OFFLOAD_PARAMS_SIZE;
	}
	params.ndis_hdr.ndis_size = paramsz;

	/*
	 * TSO4/TSO6 setup.
	 */
	tso_maxsz = IP_MAXPACKET;
	tso_minsg = 2;
	if (hwcaps.ndis_lsov2.ndis_ip4_encap & NDIS_OFFLOAD_ENCAP_8023) {
		caps |= HN_CAP_TSO4;
		params.ndis_lsov2_ip4 = NDIS_OFFLOAD_LSOV2_ON;

		if (hwcaps.ndis_lsov2.ndis_ip4_maxsz < tso_maxsz)
			tso_maxsz = hwcaps.ndis_lsov2.ndis_ip4_maxsz;
		if (hwcaps.ndis_lsov2.ndis_ip4_minsg > tso_minsg)
			tso_minsg = hwcaps.ndis_lsov2.ndis_ip4_minsg;
	}
	if ((hwcaps.ndis_lsov2.ndis_ip6_encap & NDIS_OFFLOAD_ENCAP_8023) &&
	    (hwcaps.ndis_lsov2.ndis_ip6_opts & HN_NDIS_LSOV2_CAP_IP6) ==
	    HN_NDIS_LSOV2_CAP_IP6) {
		caps |= HN_CAP_TSO6;
		params.ndis_lsov2_ip6 = NDIS_OFFLOAD_LSOV2_ON;

		if (hwcaps.ndis_lsov2.ndis_ip6_maxsz < tso_maxsz)
			tso_maxsz = hwcaps.ndis_lsov2.ndis_ip6_maxsz;
		if (hwcaps.ndis_lsov2.ndis_ip6_minsg > tso_minsg)
			tso_minsg = hwcaps.ndis_lsov2.ndis_ip6_minsg;
	}
	sc->hn_ndis_tso_szmax = 0;
	sc->hn_ndis_tso_sgmin = 0;
	if (caps & (HN_CAP_TSO4 | HN_CAP_TSO6)) {
		KASSERT(tso_maxsz <= IP_MAXPACKET,
		    ("invalid NDIS TSO maxsz %d", tso_maxsz));
		KASSERT(tso_minsg >= 2,
		    ("invalid NDIS TSO minsg %d", tso_minsg));
		if (tso_maxsz < tso_minsg * mtu) {
			if_printf(sc->hn_ifp, "invalid NDIS TSO config: "
			    "maxsz %d, minsg %d, mtu %d; "
			    "disable TSO4 and TSO6\n",
			    tso_maxsz, tso_minsg, mtu);
			caps &= ~(HN_CAP_TSO4 | HN_CAP_TSO6);
			params.ndis_lsov2_ip4 = NDIS_OFFLOAD_LSOV2_OFF;
			params.ndis_lsov2_ip6 = NDIS_OFFLOAD_LSOV2_OFF;
		} else {
			sc->hn_ndis_tso_szmax = tso_maxsz;
			sc->hn_ndis_tso_sgmin = tso_minsg;
			if (bootverbose) {
				if_printf(sc->hn_ifp, "NDIS TSO "
				    "szmax %d sgmin %d\n",
				    sc->hn_ndis_tso_szmax,
				    sc->hn_ndis_tso_sgmin);
			}
		}
	}

	/* IPv4 checksum */
	if ((hwcaps.ndis_csum.ndis_ip4_txcsum & HN_NDIS_TXCSUM_CAP_IP4) ==
	    HN_NDIS_TXCSUM_CAP_IP4) {
		caps |= HN_CAP_IPCS;
		params.ndis_ip4csum = NDIS_OFFLOAD_PARAM_TX;
	}
	if (hwcaps.ndis_csum.ndis_ip4_rxcsum & NDIS_RXCSUM_CAP_IP4) {
		if (params.ndis_ip4csum == NDIS_OFFLOAD_PARAM_TX)
			params.ndis_ip4csum = NDIS_OFFLOAD_PARAM_TXRX;
		else
			params.ndis_ip4csum = NDIS_OFFLOAD_PARAM_RX;
	}

	/* TCP4 checksum */
	if ((hwcaps.ndis_csum.ndis_ip4_txcsum & HN_NDIS_TXCSUM_CAP_TCP4) ==
	    HN_NDIS_TXCSUM_CAP_TCP4) {
		caps |= HN_CAP_TCP4CS;
		params.ndis_tcp4csum = NDIS_OFFLOAD_PARAM_TX;
	}
	if (hwcaps.ndis_csum.ndis_ip4_rxcsum & NDIS_RXCSUM_CAP_TCP4) {
		if (params.ndis_tcp4csum == NDIS_OFFLOAD_PARAM_TX)
			params.ndis_tcp4csum = NDIS_OFFLOAD_PARAM_TXRX;
		else
			params.ndis_tcp4csum = NDIS_OFFLOAD_PARAM_RX;
	}

	/* UDP4 checksum */
	if (hwcaps.ndis_csum.ndis_ip4_txcsum & NDIS_TXCSUM_CAP_UDP4) {
		caps |= HN_CAP_UDP4CS;
		params.ndis_udp4csum = NDIS_OFFLOAD_PARAM_TX;
	}
	if (hwcaps.ndis_csum.ndis_ip4_rxcsum & NDIS_RXCSUM_CAP_UDP4) {
		if (params.ndis_udp4csum == NDIS_OFFLOAD_PARAM_TX)
			params.ndis_udp4csum = NDIS_OFFLOAD_PARAM_TXRX;
		else
			params.ndis_udp4csum = NDIS_OFFLOAD_PARAM_RX;
	}

	/* TCP6 checksum */
	if ((hwcaps.ndis_csum.ndis_ip6_txcsum & HN_NDIS_TXCSUM_CAP_TCP6) ==
	    HN_NDIS_TXCSUM_CAP_TCP6) {
		caps |= HN_CAP_TCP6CS;
		params.ndis_tcp6csum = NDIS_OFFLOAD_PARAM_TX;
	}
	if (hwcaps.ndis_csum.ndis_ip6_rxcsum & NDIS_RXCSUM_CAP_TCP6) {
		if (params.ndis_tcp6csum == NDIS_OFFLOAD_PARAM_TX)
			params.ndis_tcp6csum = NDIS_OFFLOAD_PARAM_TXRX;
		else
			params.ndis_tcp6csum = NDIS_OFFLOAD_PARAM_RX;
	}

	/* UDP6 checksum */
	if ((hwcaps.ndis_csum.ndis_ip6_txcsum & HN_NDIS_TXCSUM_CAP_UDP6) ==
	    HN_NDIS_TXCSUM_CAP_UDP6) {
		caps |= HN_CAP_UDP6CS;
		params.ndis_udp6csum = NDIS_OFFLOAD_PARAM_TX;
	}
	if (hwcaps.ndis_csum.ndis_ip6_rxcsum & NDIS_RXCSUM_CAP_UDP6) {
		if (params.ndis_udp6csum == NDIS_OFFLOAD_PARAM_TX)
			params.ndis_udp6csum = NDIS_OFFLOAD_PARAM_TXRX;
		else
			params.ndis_udp6csum = NDIS_OFFLOAD_PARAM_RX;
	}

	if (bootverbose) {
		if_printf(sc->hn_ifp, "offload csum: "
		    "ip4 %u, tcp4 %u, udp4 %u, tcp6 %u, udp6 %u\n",
		    params.ndis_ip4csum,
		    params.ndis_tcp4csum,
		    params.ndis_udp4csum,
		    params.ndis_tcp6csum,
		    params.ndis_udp6csum);
		if_printf(sc->hn_ifp, "offload lsov2: ip4 %u, ip6 %u\n",
		    params.ndis_lsov2_ip4,
		    params.ndis_lsov2_ip6);
	}

	error = hn_rndis_set(sc, OID_TCP_OFFLOAD_PARAMETERS, &params, paramsz);
	if (error) {
		if_printf(sc->hn_ifp, "offload config failed: %d\n", error);
		return (error);
	}

	if (bootverbose)
		if_printf(sc->hn_ifp, "offload config done\n");
	sc->hn_caps |= caps;
	return (0);
}