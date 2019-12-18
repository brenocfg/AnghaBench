#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ decode_buf; } ;
struct TYPE_5__ {TYPE_1__ mac_stats; } ;
struct sfxge_softc {TYPE_2__ port; } ;
struct ifnet {struct sfxge_softc* if_softc; } ;
typedef  int ift_counter ;

/* Variables and functions */
 size_t EFX_MAC_RX_ERRORS ; 
 size_t EFX_MAC_RX_OCTETS ; 
 size_t EFX_MAC_RX_PKTS ; 
 size_t EFX_MAC_TX_BRDCST_PKTS ; 
 size_t EFX_MAC_TX_ERRORS ; 
 size_t EFX_MAC_TX_EX_COL_PKTS ; 
 size_t EFX_MAC_TX_LATE_COL_PKTS ; 
 size_t EFX_MAC_TX_MULTICST_PKTS ; 
 size_t EFX_MAC_TX_MULT_COL_PKTS ; 
 size_t EFX_MAC_TX_OCTETS ; 
 size_t EFX_MAC_TX_PKTS ; 
 size_t EFX_MAC_TX_SGL_COL_PKTS ; 
#define  IFCOUNTER_COLLISIONS 139 
#define  IFCOUNTER_IBYTES 138 
#define  IFCOUNTER_IERRORS 137 
#define  IFCOUNTER_IMCASTS 136 
#define  IFCOUNTER_IPACKETS 135 
#define  IFCOUNTER_IQDROPS 134 
#define  IFCOUNTER_NOPROTO 133 
#define  IFCOUNTER_OBYTES 132 
#define  IFCOUNTER_OERRORS 131 
#define  IFCOUNTER_OMCASTS 130 
#define  IFCOUNTER_OPACKETS 129 
#define  IFCOUNTER_OQDROPS 128 
 int /*<<< orphan*/  SFXGE_PORT_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  SFXGE_PORT_UNLOCK (TYPE_2__*) ; 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 int /*<<< orphan*/  sfxge_mac_stat_update (struct sfxge_softc*) ; 
 scalar_t__ sfxge_tx_get_drops (struct sfxge_softc*) ; 

uint64_t
sfxge_get_counter(struct ifnet *ifp, ift_counter c)
{
	struct sfxge_softc *sc = ifp->if_softc;
	uint64_t *mac_stats;
	uint64_t val;

	SFXGE_PORT_LOCK(&sc->port);

	/* Ignore error and use old values */
	(void)sfxge_mac_stat_update(sc);

	mac_stats = (uint64_t *)sc->port.mac_stats.decode_buf;

	switch (c) {
	case IFCOUNTER_IPACKETS:
		val = mac_stats[EFX_MAC_RX_PKTS];
		break;
	case IFCOUNTER_IERRORS:
		val = mac_stats[EFX_MAC_RX_ERRORS];
		break;
	case IFCOUNTER_OPACKETS:
		val = mac_stats[EFX_MAC_TX_PKTS];
		break;
	case IFCOUNTER_OERRORS:
		val = mac_stats[EFX_MAC_TX_ERRORS];
		break;
	case IFCOUNTER_COLLISIONS:
		val = mac_stats[EFX_MAC_TX_SGL_COL_PKTS] +
		      mac_stats[EFX_MAC_TX_MULT_COL_PKTS] +
		      mac_stats[EFX_MAC_TX_EX_COL_PKTS] +
		      mac_stats[EFX_MAC_TX_LATE_COL_PKTS];
		break;
	case IFCOUNTER_IBYTES:
		val = mac_stats[EFX_MAC_RX_OCTETS];
		break;
	case IFCOUNTER_OBYTES:
		val = mac_stats[EFX_MAC_TX_OCTETS];
		break;
	case IFCOUNTER_OMCASTS:
		val = mac_stats[EFX_MAC_TX_MULTICST_PKTS] +
		      mac_stats[EFX_MAC_TX_BRDCST_PKTS];
		break;
	case IFCOUNTER_OQDROPS:
		SFXGE_PORT_UNLOCK(&sc->port);
		return (sfxge_tx_get_drops(sc));
	case IFCOUNTER_IMCASTS:
		/* if_imcasts is maintained in net/if_ethersubr.c */
	case IFCOUNTER_IQDROPS:
		/* if_iqdrops is maintained in net/if_ethersubr.c */
	case IFCOUNTER_NOPROTO:
		/* if_noproto is maintained in net/if_ethersubr.c */
	default:
		SFXGE_PORT_UNLOCK(&sc->port);
		return (if_get_counter_default(ifp, c));
	}

	SFXGE_PORT_UNLOCK(&sc->port);

	return (val);
}