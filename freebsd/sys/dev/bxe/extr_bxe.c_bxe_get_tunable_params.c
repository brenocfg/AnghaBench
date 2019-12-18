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
struct bxe_softc {int max_rx_bufs; int hc_rx_ticks; int hc_tx_ticks; int max_aggregation_size; int mrrs; int autogreeen; int udp_rss; int num_queues; scalar_t__ interrupt_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 scalar_t__ INTR_MODE_INTX ; 
 scalar_t__ INTR_MODE_MSI ; 
 scalar_t__ INTR_MODE_MSIX ; 
 scalar_t__ MAX_RSS_CHAINS ; 
 int RX_BD_USABLE ; 
 int TPA_AGG_SIZE ; 
 int bxe_autogreeen ; 
 int /*<<< orphan*/  bxe_debug ; 
 int bxe_hc_rx_ticks ; 
 int bxe_hc_tx_ticks ; 
 scalar_t__ bxe_interrupt_mode ; 
 int bxe_max_aggregation_size ; 
 int bxe_max_rx_bufs ; 
 int bxe_mrrs ; 
 scalar_t__ bxe_queue_count ; 
 int /*<<< orphan*/  bxe_rx_budget ; 
 int bxe_udp_rss ; 
 int min (scalar_t__,scalar_t__) ; 
 scalar_t__ mp_ncpus ; 

__attribute__((used)) static void
bxe_get_tunable_params(struct bxe_softc *sc)
{
    /* sanity checks */

    if ((bxe_interrupt_mode != INTR_MODE_INTX) &&
        (bxe_interrupt_mode != INTR_MODE_MSI)  &&
        (bxe_interrupt_mode != INTR_MODE_MSIX)) {
        BLOGW(sc, "invalid interrupt_mode value (%d)\n", bxe_interrupt_mode);
        bxe_interrupt_mode = INTR_MODE_MSIX;
    }

    if ((bxe_queue_count < 0) || (bxe_queue_count > MAX_RSS_CHAINS)) {
        BLOGW(sc, "invalid queue_count value (%d)\n", bxe_queue_count);
        bxe_queue_count = 0;
    }

    if ((bxe_max_rx_bufs < 1) || (bxe_max_rx_bufs > RX_BD_USABLE)) {
        if (bxe_max_rx_bufs == 0) {
            bxe_max_rx_bufs = RX_BD_USABLE;
        } else {
            BLOGW(sc, "invalid max_rx_bufs (%d)\n", bxe_max_rx_bufs);
            bxe_max_rx_bufs = 2048;
        }
    }

    if ((bxe_hc_rx_ticks < 1) || (bxe_hc_rx_ticks > 100)) {
        BLOGW(sc, "invalid hc_rx_ticks (%d)\n", bxe_hc_rx_ticks);
        bxe_hc_rx_ticks = 25;
    }

    if ((bxe_hc_tx_ticks < 1) || (bxe_hc_tx_ticks > 100)) {
        BLOGW(sc, "invalid hc_tx_ticks (%d)\n", bxe_hc_tx_ticks);
        bxe_hc_tx_ticks = 50;
    }

    if (bxe_max_aggregation_size == 0) {
        bxe_max_aggregation_size = TPA_AGG_SIZE;
    }

    if (bxe_max_aggregation_size > 0xffff) {
        BLOGW(sc, "invalid max_aggregation_size (%d)\n",
              bxe_max_aggregation_size);
        bxe_max_aggregation_size = TPA_AGG_SIZE;
    }

    if ((bxe_mrrs < -1) || (bxe_mrrs > 3)) {
        BLOGW(sc, "invalid mrrs (%d)\n", bxe_mrrs);
        bxe_mrrs = -1;
    }

    if ((bxe_autogreeen < 0) || (bxe_autogreeen > 2)) {
        BLOGW(sc, "invalid autogreeen (%d)\n", bxe_autogreeen);
        bxe_autogreeen = 0;
    }

    if ((bxe_udp_rss < 0) || (bxe_udp_rss > 1)) {
        BLOGW(sc, "invalid udp_rss (%d)\n", bxe_udp_rss);
        bxe_udp_rss = 0;
    }

    /* pull in user settings */

    sc->interrupt_mode       = bxe_interrupt_mode;
    sc->max_rx_bufs          = bxe_max_rx_bufs;
    sc->hc_rx_ticks          = bxe_hc_rx_ticks;
    sc->hc_tx_ticks          = bxe_hc_tx_ticks;
    sc->max_aggregation_size = bxe_max_aggregation_size;
    sc->mrrs                 = bxe_mrrs;
    sc->autogreeen           = bxe_autogreeen;
    sc->udp_rss              = bxe_udp_rss;

    if (bxe_interrupt_mode == INTR_MODE_INTX) {
        sc->num_queues = 1;
    } else { /* INTR_MODE_MSI or INTR_MODE_MSIX */
        sc->num_queues =
            min((bxe_queue_count ? bxe_queue_count : mp_ncpus),
                MAX_RSS_CHAINS);
        if (sc->num_queues > mp_ncpus) {
            sc->num_queues = mp_ncpus;
        }
    }

    BLOGD(sc, DBG_LOAD,
          "User Config: "
          "debug=0x%lx "
          "interrupt_mode=%d "
          "queue_count=%d "
          "hc_rx_ticks=%d "
          "hc_tx_ticks=%d "
          "rx_budget=%d "
          "max_aggregation_size=%d "
          "mrrs=%d "
          "autogreeen=%d "
          "udp_rss=%d\n",
          bxe_debug,
          sc->interrupt_mode,
          sc->num_queues,
          sc->hc_rx_ticks,
          sc->hc_tx_ticks,
          bxe_rx_budget,
          sc->max_aggregation_size,
          sc->mrrs,
          sc->autogreeen,
          sc->udp_rss);
}