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
struct elink_params {scalar_t__ port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XOFF_RCVD ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XOFF_RCVD_COUNT ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XOFF_SENT ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XOFF_SENT_COUNT ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XON_RCVD ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XON_RCVD_COUNT ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XON_SENT ; 
 scalar_t__ EMAC_REG_RX_PFC_STATS_XON_SENT_COUNT ; 
 scalar_t__ GRCBASE_EMAC0 ; 
 scalar_t__ GRCBASE_EMAC1 ; 
 scalar_t__ REG_RD (struct bxe_softc*,scalar_t__) ; 

__attribute__((used)) static void elink_emac_get_pfc_stat(struct elink_params *params,
				    uint32_t pfc_frames_sent[2],
				    uint32_t pfc_frames_received[2])
{
	/* Read pfc statistic */
	struct bxe_softc *sc = params->sc;
	uint32_t emac_base = params->port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	uint32_t val_xon = 0;
	uint32_t val_xoff = 0;

	ELINK_DEBUG_P0(sc, "pfc statistic read from EMAC\n");

	/* PFC received frames */
	val_xoff = REG_RD(sc, emac_base +
				EMAC_REG_RX_PFC_STATS_XOFF_RCVD);
	val_xoff &= EMAC_REG_RX_PFC_STATS_XOFF_RCVD_COUNT;
	val_xon = REG_RD(sc, emac_base + EMAC_REG_RX_PFC_STATS_XON_RCVD);
	val_xon &= EMAC_REG_RX_PFC_STATS_XON_RCVD_COUNT;

	pfc_frames_received[0] = val_xon + val_xoff;

	/* PFC received sent */
	val_xoff = REG_RD(sc, emac_base +
				EMAC_REG_RX_PFC_STATS_XOFF_SENT);
	val_xoff &= EMAC_REG_RX_PFC_STATS_XOFF_SENT_COUNT;
	val_xon = REG_RD(sc, emac_base + EMAC_REG_RX_PFC_STATS_XON_SENT);
	val_xon &= EMAC_REG_RX_PFC_STATS_XON_SENT_COUNT;

	pfc_frames_sent[0] = val_xon + val_xoff;
}