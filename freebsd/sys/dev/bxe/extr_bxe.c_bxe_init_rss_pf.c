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
typedef  int uint8_t ;
struct TYPE_4__ {scalar_t__ pmf; } ;
struct TYPE_5__ {int udp_rss_v4; int udp_rss_v6; scalar_t__* ind_table; } ;
struct bxe_softc {TYPE_1__ port; TYPE_2__ rss_conf_obj; scalar_t__ udp_rss; TYPE_3__* fp; } ;
struct TYPE_6__ {scalar_t__ cl_id; } ;

/* Variables and functions */
 int BXE_NUM_ETH_QUEUES (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int bxe_config_rss_eth (struct bxe_softc*,int) ; 

__attribute__((used)) static int
bxe_init_rss_pf(struct bxe_softc *sc)
{
    uint8_t num_eth_queues = BXE_NUM_ETH_QUEUES(sc);
    int i;

    /*
     * Prepare the initial contents of the indirection table if
     * RSS is enabled
     */
    for (i = 0; i < sizeof(sc->rss_conf_obj.ind_table); i++) {
        sc->rss_conf_obj.ind_table[i] =
            (sc->fp->cl_id + (i % num_eth_queues));
    }

    if (sc->udp_rss) {
        sc->rss_conf_obj.udp_rss_v4 = sc->rss_conf_obj.udp_rss_v6 = 1;
    }

    /*
     * For 57710 and 57711 SEARCHER configuration (rss_keys) is
     * per-port, so if explicit configuration is needed, do it only
     * for a PMF.
     *
     * For 57712 and newer it's a per-function configuration.
     */
    return (bxe_config_rss_eth(sc, sc->port.pmf || !CHIP_IS_E1x(sc)));
}