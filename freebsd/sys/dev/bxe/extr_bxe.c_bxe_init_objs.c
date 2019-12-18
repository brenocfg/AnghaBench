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
struct bxe_softc {int flags; int /*<<< orphan*/  sp_state; TYPE_1__* fp; int /*<<< orphan*/  rss_conf_obj; int /*<<< orphan*/  vlans_pool; int /*<<< orphan*/  macs_pool; int /*<<< orphan*/  mcast_obj; int /*<<< orphan*/  rx_mode_obj; } ;
typedef  int /*<<< orphan*/  ecore_obj_type ;
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  cl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_SP_MAPPING (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int BXE_TX_SWITCHING ; 
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_FILTER_MCAST_PENDING ; 
 int /*<<< orphan*/  ECORE_FILTER_RSS_CONF_PENDING ; 
 int /*<<< orphan*/  ECORE_OBJ_TYPE_RX ; 
 int /*<<< orphan*/  ECORE_OBJ_TYPE_RX_TX ; 
 int SC_ABS_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  VNICS_PER_PATH (struct bxe_softc*) ; 
 int /*<<< orphan*/  VNICS_PER_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_init_mac_credit_pool (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_mcast_obj (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_rss_config_obj (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_rx_mode_obj (struct bxe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_init_vlan_credit_pool (struct bxe_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcast_rdata ; 
 int /*<<< orphan*/  rss_rdata ; 

__attribute__((used)) static inline void
bxe_init_objs(struct bxe_softc *sc)
{
    /* mcast rules must be added to tx if tx switching is enabled */
    ecore_obj_type o_type =
        (sc->flags & BXE_TX_SWITCHING) ? ECORE_OBJ_TYPE_RX_TX :
                                         ECORE_OBJ_TYPE_RX;

    /* RX_MODE controlling object */
    ecore_init_rx_mode_obj(sc, &sc->rx_mode_obj);

    /* multicast configuration controlling object */
    ecore_init_mcast_obj(sc,
                         &sc->mcast_obj,
                         sc->fp[0].cl_id,
                         sc->fp[0].index,
                         SC_FUNC(sc),
                         SC_FUNC(sc),
                         BXE_SP(sc, mcast_rdata),
                         BXE_SP_MAPPING(sc, mcast_rdata),
                         ECORE_FILTER_MCAST_PENDING,
                         &sc->sp_state,
                         o_type);

    /* Setup CAM credit pools */
    ecore_init_mac_credit_pool(sc,
                               &sc->macs_pool,
                               SC_FUNC(sc),
                               CHIP_IS_E1x(sc) ? VNICS_PER_PORT(sc) :
                                                 VNICS_PER_PATH(sc));

    ecore_init_vlan_credit_pool(sc,
                                &sc->vlans_pool,
                                SC_ABS_FUNC(sc) >> 1,
                                CHIP_IS_E1x(sc) ? VNICS_PER_PORT(sc) :
                                                  VNICS_PER_PATH(sc));

    /* RSS configuration object */
    ecore_init_rss_config_obj(sc,
                              &sc->rss_conf_obj,
                              sc->fp[0].cl_id,
                              sc->fp[0].index,
                              SC_FUNC(sc),
                              SC_FUNC(sc),
                              BXE_SP(sc, rss_rdata),
                              BXE_SP_MAPPING(sc, rss_rdata),
                              ECORE_FILTER_RSS_CONF_PENDING,
                              &sc->sp_state, ECORE_OBJ_TYPE_RX);
}