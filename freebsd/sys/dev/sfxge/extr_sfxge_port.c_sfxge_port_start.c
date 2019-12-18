#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr_dl {int dummy; } ;
struct TYPE_7__ {TYPE_2__* ifm_cur; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma_buf; } ;
struct sfxge_port {scalar_t__ init_state; TYPE_4__ mac_stats; int /*<<< orphan*/  stats_update_period_ms; } ;
struct sfxge_softc {int /*<<< orphan*/ * enp; TYPE_3__ media; struct sfxge_port port; struct ifnet* ifnet; } ;
struct ifnet {TYPE_1__* if_addr; int /*<<< orphan*/  if_mtu; } ;
struct epoch_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  mac_addr ;
typedef  int /*<<< orphan*/  efx_nic_t ;
struct TYPE_6__ {int /*<<< orphan*/  ifm_media; } ;
struct TYPE_5__ {scalar_t__ ifa_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t EFX_MAC_PDU (int /*<<< orphan*/ ) ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 scalar_t__ SFXGE_PORT_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_PORT_LOCK (struct sfxge_port*) ; 
 scalar_t__ SFXGE_PORT_STARTED ; 
 int /*<<< orphan*/  SFXGE_PORT_UNLOCK (struct sfxge_port*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  efx_filter_fini (int /*<<< orphan*/ *) ; 
 int efx_filter_init (int /*<<< orphan*/ *) ; 
 int efx_mac_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int efx_mac_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int efx_mac_fcntl_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_mac_pdu_set (int /*<<< orphan*/ *,size_t) ; 
 int efx_mac_stats_periodic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_phy_adv_cap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_port_fini (int /*<<< orphan*/ *) ; 
 int efx_port_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_mac_filter_set_locked (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_mac_poll_work (struct sfxge_softc*,int /*<<< orphan*/ ) ; 
 int sfxge_phy_cap_mask (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_port_wanted_fc (struct sfxge_softc*) ; 

int
sfxge_port_start(struct sfxge_softc *sc)
{
	uint8_t mac_addr[ETHER_ADDR_LEN];
	struct epoch_tracker et;
	struct ifnet *ifp = sc->ifnet;
	struct sfxge_port *port;
	efx_nic_t *enp;
	size_t pdu;
	int rc;
	uint32_t phy_cap_mask;

	port = &sc->port;
	enp = sc->enp;

	SFXGE_PORT_LOCK(port);

	KASSERT(port->init_state == SFXGE_PORT_INITIALIZED,
	    ("port not initialized"));

	/* Initialise the required filtering */
	if ((rc = efx_filter_init(enp)) != 0)
		goto fail_filter_init;

	/* Initialize the port object in the common code. */
	if ((rc = efx_port_init(sc->enp)) != 0)
		goto fail;

	/* Set the SDU */
	pdu = EFX_MAC_PDU(ifp->if_mtu);
	if ((rc = efx_mac_pdu_set(enp, pdu)) != 0)
		goto fail2;

	if ((rc = efx_mac_fcntl_set(enp, sfxge_port_wanted_fc(sc), B_TRUE))
	    != 0)
		goto fail3;

	/* Set the unicast address */
	NET_EPOCH_ENTER(et);
	bcopy(LLADDR((struct sockaddr_dl *)ifp->if_addr->ifa_addr),
	      mac_addr, sizeof(mac_addr));
	NET_EPOCH_EXIT(et);
	if ((rc = efx_mac_addr_set(enp, mac_addr)) != 0)
		goto fail4;

	sfxge_mac_filter_set_locked(sc);

	/* Update MAC stats by DMA every period */
	if ((rc = efx_mac_stats_periodic(enp, &port->mac_stats.dma_buf,
					 port->stats_update_period_ms,
					 B_FALSE)) != 0)
		goto fail6;

	if ((rc = efx_mac_drain(enp, B_FALSE)) != 0)
		goto fail8;

	if ((rc = sfxge_phy_cap_mask(sc, sc->media.ifm_cur->ifm_media,
				     &phy_cap_mask)) != 0)
		goto fail9;

	if ((rc = efx_phy_adv_cap_set(sc->enp, phy_cap_mask)) != 0)
		goto fail10;

	port->init_state = SFXGE_PORT_STARTED;

	/* Single poll in case there were missing initial events */
	SFXGE_PORT_UNLOCK(port);
	sfxge_mac_poll_work(sc, 0);

	return (0);

fail10:
fail9:
	(void)efx_mac_drain(enp, B_TRUE);
fail8:
	(void)efx_mac_stats_periodic(enp, &port->mac_stats.dma_buf, 0, B_FALSE);
fail6:
fail4:
fail3:

fail2:
	efx_port_fini(enp);
fail:
	efx_filter_fini(enp);
fail_filter_init:
	SFXGE_PORT_UNLOCK(port);

	return (rc);
}