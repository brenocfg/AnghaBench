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
typedef  scalar_t__ uint32_t ;
struct nig_stats {scalar_t__ brb_truncate; scalar_t__ brb_discard; } ;
struct mac_stx {int dummy; } ;
struct host_port_stats {int /*<<< orphan*/  host_port_stats_counter; int /*<<< orphan*/  brb_drop_lo; int /*<<< orphan*/  brb_drop_hi; struct nig_stats* mac_stx; } ;
struct TYPE_5__ {int mac_type; } ;
struct bxe_eth_stats {scalar_t__ nig_timer_max; int /*<<< orphan*/  eee_tx_lpi; int /*<<< orphan*/  brb_drop_lo; int /*<<< orphan*/  brb_drop_hi; struct nig_stats rx_stat_ifhcinbadoctets_hi; int /*<<< orphan*/  brb_truncate_lo; int /*<<< orphan*/  brb_truncate_hi; } ;
struct TYPE_4__ {struct nig_stats old_nig_stats; } ;
struct bxe_softc {TYPE_2__ link_vars; struct bxe_eth_stats eth_stats; TYPE_1__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  stat_nig_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_EXTEND_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int /*<<< orphan*/  BXE_NOMCP (struct bxe_softc*) ; 
 void* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_STATS ; 
#define  ELINK_MAC_TYPE_BMAC 132 
#define  ELINK_MAC_TYPE_EMAC 131 
#define  ELINK_MAC_TYPE_NONE 130 
#define  ELINK_MAC_TYPE_UMAC 129 
#define  ELINK_MAC_TYPE_XMAC 128 
 scalar_t__ MISC_REG_CPMU_LP_SM_ENT_CNT_P0 ; 
 scalar_t__ MISC_REG_CPMU_LP_SM_ENT_CNT_P1 ; 
 scalar_t__ REG_RD (struct bxe_softc*,scalar_t__) ; 
 size_t SC_PORT (struct bxe_softc*) ; 
 scalar_t__ SHMEM_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_STAT64_NIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_bmac_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_emac_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_mstat_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  egress_mac_pkt0 ; 
 int /*<<< orphan*/  egress_mac_pkt1 ; 
 int /*<<< orphan*/  etherstatspkts1024octetsto1522octets ; 
 int /*<<< orphan*/  etherstatspktsover1522octets ; 
 int /*<<< orphan*/  memcpy (struct nig_stats*,struct nig_stats*,int) ; 
 int /*<<< orphan*/  nig_stats ; 
 TYPE_3__* port_mb ; 
 int /*<<< orphan*/  port_stats ; 

__attribute__((used)) static int
bxe_hw_stats_update(struct bxe_softc *sc)
{
    struct nig_stats *new = BXE_SP(sc, nig_stats);
    struct nig_stats *old = &(sc->port.old_nig_stats);
    struct host_port_stats *pstats = BXE_SP(sc, port_stats);
    struct bxe_eth_stats *estats = &sc->eth_stats;
    uint32_t lpi_reg, nig_timer_max;
    struct {
        uint32_t lo;
        uint32_t hi;
    } diff;

    switch (sc->link_vars.mac_type) {
    case ELINK_MAC_TYPE_BMAC:
        bxe_bmac_stats_update(sc);
        break;

    case ELINK_MAC_TYPE_EMAC:
        bxe_emac_stats_update(sc);
        break;

    case ELINK_MAC_TYPE_UMAC:
    case ELINK_MAC_TYPE_XMAC:
        bxe_mstat_stats_update(sc);
        break;

    case ELINK_MAC_TYPE_NONE: /* unreached */
        BLOGD(sc, DBG_STATS,
              "stats updated by DMAE but no MAC active\n");
        return (-1);

    default: /* unreached */
        BLOGE(sc, "stats update failed, unknown MAC type\n");
    }

    ADD_EXTEND_64(pstats->brb_drop_hi, pstats->brb_drop_lo,
                  new->brb_discard - old->brb_discard);
    ADD_EXTEND_64(estats->brb_truncate_hi, estats->brb_truncate_lo,
                  new->brb_truncate - old->brb_truncate);

    if (!CHIP_IS_E3(sc)) {
        UPDATE_STAT64_NIG(egress_mac_pkt0,
                          etherstatspkts1024octetsto1522octets);
        UPDATE_STAT64_NIG(egress_mac_pkt1,
                          etherstatspktsover1522octets);
    }

    memcpy(old, new, sizeof(struct nig_stats));

    memcpy(&(estats->rx_stat_ifhcinbadoctets_hi), &(pstats->mac_stx[1]),
           sizeof(struct mac_stx));
    estats->brb_drop_hi = pstats->brb_drop_hi;
    estats->brb_drop_lo = pstats->brb_drop_lo;

    pstats->host_port_stats_counter++;

    if (CHIP_IS_E3(sc)) {
        lpi_reg = (SC_PORT(sc)) ?
                      MISC_REG_CPMU_LP_SM_ENT_CNT_P1 :
                      MISC_REG_CPMU_LP_SM_ENT_CNT_P0;
        estats->eee_tx_lpi += REG_RD(sc, lpi_reg);
    }

    if (!BXE_NOMCP(sc)) {
        nig_timer_max = SHMEM_RD(sc, port_mb[SC_PORT(sc)].stat_nig_timer);
        if (nig_timer_max != estats->nig_timer_max) {
            estats->nig_timer_max = nig_timer_max;
	    /*NOTE: not setting error bit */
            BLOGE(sc, "invalid NIG timer max (%u)\n",
                  estats->nig_timer_max);
        }
    }

    return (0);
}