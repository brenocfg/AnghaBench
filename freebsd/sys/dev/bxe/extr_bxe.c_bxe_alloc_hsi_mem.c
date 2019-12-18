#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union event_ring_elem {int dummy; } event_ring_elem ;
struct eth_tx_next_bd {void* addr_lo; void* addr_hi; } ;
union eth_tx_bd_types {struct eth_tx_next_bd next_bd; } ;
typedef  union eth_rx_cqe {int dummy; } eth_rx_cqe ;
typedef  union bxe_host_hc_status_block {int dummy; } bxe_host_hc_status_block ;
struct host_sp_status_block {int dummy; } ;
struct host_hc_status_block_e2 {int dummy; } ;
struct host_hc_status_block_e1x {int dummy; } ;
struct eth_spe {int dummy; } ;
struct eth_rx_sge {void* addr_lo; void* addr_hi; } ;
struct eth_rx_cqe_next_page {void* addr_lo; void* addr_hi; } ;
struct eth_rx_bd {void* addr_lo; void* addr_hi; } ;
struct TYPE_15__ {scalar_t__ paddr; scalar_t__ vaddr; } ;
struct bxe_softc {int num_queues; int /*<<< orphan*/  parent_dma_tag; int /*<<< orphan*/  ifp; struct bxe_fastpath* fp; struct host_sp_status_block* def_sb; TYPE_7__ def_sb_dma; union event_ring_elem* eq; TYPE_7__ eq_dma; struct bxe_slowpath* sp; TYPE_7__ sp_dma; struct eth_spe* spq; TYPE_7__ spq_dma; int /*<<< orphan*/ * gz_buf; TYPE_7__ gz_buf_dma; int /*<<< orphan*/ * gz_strm; int /*<<< orphan*/  dev; } ;
struct bxe_slowpath {int dummy; } ;
struct TYPE_9__ {struct host_hc_status_block_e1x* e1x_sb; struct host_hc_status_block_e2* e2_sb; } ;
struct bxe_fastpath {int index; int /*<<< orphan*/  rx_tpa_info_mbuf_spare_map; int /*<<< orphan*/  rx_mbuf_tag; TYPE_6__* rx_tpa_info; int /*<<< orphan*/  rx_sge_mbuf_spare_map; int /*<<< orphan*/  rx_sge_mbuf_tag; TYPE_4__* rx_sge_mbuf_chain; int /*<<< orphan*/  rx_mbuf_spare_map; TYPE_3__* rx_mbuf_chain; TYPE_2__* tx_mbuf_chain; int /*<<< orphan*/  tx_mbuf_tag; TYPE_7__ rx_sge_dma; struct eth_rx_sge* rx_sge_chain; TYPE_7__ rcq_dma; union eth_rx_cqe* rcq_chain; TYPE_7__ rx_dma; struct eth_rx_bd* rx_chain; TYPE_7__ tx_dma; union eth_tx_bd_types* tx_chain; TYPE_7__ sb_dma; TYPE_1__ status_block; struct bxe_softc* sc; } ;
typedef  int bus_size_t ;
typedef  scalar_t__ bus_addr_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_13__ {int /*<<< orphan*/  m_map; } ;
struct TYPE_14__ {TYPE_5__ bd; } ;
struct TYPE_12__ {int /*<<< orphan*/  m_map; } ;
struct TYPE_11__ {int /*<<< orphan*/  m_map; } ;
struct TYPE_10__ {int /*<<< orphan*/  m_map; } ;

/* Variables and functions */
 int BCM_PAGE_SIZE ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_UNRESTRICTED ; 
 int BXE_MAX_SEGMENTS ; 
 int BXE_TSO_MAX_SEGMENTS ; 
 int BXE_TSO_MAX_SEG_SIZE ; 
 int BXE_TSO_MAX_SIZE ; 
 scalar_t__ CHIP_IS_E2E3 (struct bxe_softc*) ; 
 int FW_BUF_SIZE ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int MAX_AGG_QS (struct bxe_softc*) ; 
 int MCLBYTES ; 
 int MJUM9BYTES ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int RCQ_NUM_PAGES ; 
 int RCQ_TOTAL_PER_PAGE ; 
 int RX_BD_NUM_PAGES ; 
 int RX_BD_TOTAL ; 
 int RX_BD_TOTAL_PER_PAGE ; 
 int RX_SGE_NUM_PAGES ; 
 int RX_SGE_TOTAL ; 
 int RX_SGE_TOTAL_PER_PAGE ; 
 int TX_BD_NUM_PAGES ; 
 int TX_BD_TOTAL ; 
 int TX_BD_TOTAL_PER_PAGE ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ bxe_dma_alloc (struct bxe_softc*,int,TYPE_7__*,char*) ; 
 int /*<<< orphan*/  bxe_dma_free (struct bxe_softc*,TYPE_7__*) ; 
 int /*<<< orphan*/  bxe_init_sge_ring_bit_mask (struct bxe_fastpath*) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
bxe_alloc_hsi_mem(struct bxe_softc *sc)
{
    struct bxe_fastpath *fp;
    bus_addr_t busaddr;
    int max_agg_queues;
    int max_segments;
    bus_size_t max_size;
    bus_size_t max_seg_size;
    char buf[32];
    int rc;
    int i, j;

    /* XXX zero out all vars here and call bxe_alloc_hsi_mem on error */

    /* allocate the parent bus DMA tag */
    rc = bus_dma_tag_create(bus_get_dma_tag(sc->dev), /* parent tag */
                            1,                        /* alignment */
                            0,                        /* boundary limit */
                            BUS_SPACE_MAXADDR,        /* restricted low */
                            BUS_SPACE_MAXADDR,        /* restricted hi */
                            NULL,                     /* addr filter() */
                            NULL,                     /* addr filter() arg */
                            BUS_SPACE_MAXSIZE_32BIT,  /* max map size */
                            BUS_SPACE_UNRESTRICTED,   /* num discontinuous */
                            BUS_SPACE_MAXSIZE_32BIT,  /* max seg size */
                            0,                        /* flags */
                            NULL,                     /* lock() */
                            NULL,                     /* lock() arg */
                            &sc->parent_dma_tag);     /* returned dma tag */
    if (rc != 0) {
        BLOGE(sc, "Failed to alloc parent DMA tag (%d)!\n", rc);
        return (1);
    }

    /************************/
    /* DEFAULT STATUS BLOCK */
    /************************/

    if (bxe_dma_alloc(sc, sizeof(struct host_sp_status_block),
                      &sc->def_sb_dma, "default status block") != 0) {
        /* XXX */
        bus_dma_tag_destroy(sc->parent_dma_tag);
        return (1);
    }

    sc->def_sb = (struct host_sp_status_block *)sc->def_sb_dma.vaddr;

    /***************/
    /* EVENT QUEUE */
    /***************/

    if (bxe_dma_alloc(sc, BCM_PAGE_SIZE,
                      &sc->eq_dma, "event queue") != 0) {
        /* XXX */
        bxe_dma_free(sc, &sc->def_sb_dma);
        sc->def_sb = NULL;
        bus_dma_tag_destroy(sc->parent_dma_tag);
        return (1);
    }

    sc->eq = (union event_ring_elem * )sc->eq_dma.vaddr;

    /*************/
    /* SLOW PATH */
    /*************/

    if (bxe_dma_alloc(sc, sizeof(struct bxe_slowpath),
                      &sc->sp_dma, "slow path") != 0) {
        /* XXX */
        bxe_dma_free(sc, &sc->eq_dma);
        sc->eq = NULL;
        bxe_dma_free(sc, &sc->def_sb_dma);
        sc->def_sb = NULL;
        bus_dma_tag_destroy(sc->parent_dma_tag);
        return (1);
    }

    sc->sp = (struct bxe_slowpath *)sc->sp_dma.vaddr;

    /*******************/
    /* SLOW PATH QUEUE */
    /*******************/

    if (bxe_dma_alloc(sc, BCM_PAGE_SIZE,
                      &sc->spq_dma, "slow path queue") != 0) {
        /* XXX */
        bxe_dma_free(sc, &sc->sp_dma);
        sc->sp = NULL;
        bxe_dma_free(sc, &sc->eq_dma);
        sc->eq = NULL;
        bxe_dma_free(sc, &sc->def_sb_dma);
        sc->def_sb = NULL;
        bus_dma_tag_destroy(sc->parent_dma_tag);
        return (1);
    }

    sc->spq = (struct eth_spe *)sc->spq_dma.vaddr;

    /***************************/
    /* FW DECOMPRESSION BUFFER */
    /***************************/

    if (bxe_dma_alloc(sc, FW_BUF_SIZE, &sc->gz_buf_dma,
                      "fw decompression buffer") != 0) {
        /* XXX */
        bxe_dma_free(sc, &sc->spq_dma);
        sc->spq = NULL;
        bxe_dma_free(sc, &sc->sp_dma);
        sc->sp = NULL;
        bxe_dma_free(sc, &sc->eq_dma);
        sc->eq = NULL;
        bxe_dma_free(sc, &sc->def_sb_dma);
        sc->def_sb = NULL;
        bus_dma_tag_destroy(sc->parent_dma_tag);
        return (1);
    }

    sc->gz_buf = (void *)sc->gz_buf_dma.vaddr;

    if ((sc->gz_strm =
         malloc(sizeof(*sc->gz_strm), M_DEVBUF, M_NOWAIT)) == NULL) {
        /* XXX */
        bxe_dma_free(sc, &sc->gz_buf_dma);
        sc->gz_buf = NULL;
        bxe_dma_free(sc, &sc->spq_dma);
        sc->spq = NULL;
        bxe_dma_free(sc, &sc->sp_dma);
        sc->sp = NULL;
        bxe_dma_free(sc, &sc->eq_dma);
        sc->eq = NULL;
        bxe_dma_free(sc, &sc->def_sb_dma);
        sc->def_sb = NULL;
        bus_dma_tag_destroy(sc->parent_dma_tag);
        return (1);
    }

    /*************/
    /* FASTPATHS */
    /*************/

    /* allocate DMA memory for each fastpath structure */
    for (i = 0; i < sc->num_queues; i++) {
        fp = &sc->fp[i];
        fp->sc    = sc;
        fp->index = i;

        /*******************/
        /* FP STATUS BLOCK */
        /*******************/

        snprintf(buf, sizeof(buf), "fp %d status block", i);
        if (bxe_dma_alloc(sc, sizeof(union bxe_host_hc_status_block),
                          &fp->sb_dma, buf) != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to alloc %s\n", buf);
            return (1);
        } else {
            if (CHIP_IS_E2E3(sc)) {
                fp->status_block.e2_sb =
                    (struct host_hc_status_block_e2 *)fp->sb_dma.vaddr;
            } else {
                fp->status_block.e1x_sb =
                    (struct host_hc_status_block_e1x *)fp->sb_dma.vaddr;
            }
        }

        /******************/
        /* FP TX BD CHAIN */
        /******************/

        snprintf(buf, sizeof(buf), "fp %d tx bd chain", i);
        if (bxe_dma_alloc(sc, (BCM_PAGE_SIZE * TX_BD_NUM_PAGES),
                          &fp->tx_dma, buf) != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to alloc %s\n", buf);
            return (1);
        } else {
            fp->tx_chain = (union eth_tx_bd_types *)fp->tx_dma.vaddr;
        }

        /* link together the tx bd chain pages */
        for (j = 1; j <= TX_BD_NUM_PAGES; j++) {
            /* index into the tx bd chain array to last entry per page */
            struct eth_tx_next_bd *tx_next_bd =
                &fp->tx_chain[TX_BD_TOTAL_PER_PAGE * j - 1].next_bd;
            /* point to the next page and wrap from last page */
            busaddr = (fp->tx_dma.paddr +
                       (BCM_PAGE_SIZE * (j % TX_BD_NUM_PAGES)));
            tx_next_bd->addr_hi = htole32(U64_HI(busaddr));
            tx_next_bd->addr_lo = htole32(U64_LO(busaddr));
        }

        /******************/
        /* FP RX BD CHAIN */
        /******************/

        snprintf(buf, sizeof(buf), "fp %d rx bd chain", i);
        if (bxe_dma_alloc(sc, (BCM_PAGE_SIZE * RX_BD_NUM_PAGES),
                          &fp->rx_dma, buf) != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to alloc %s\n", buf);
            return (1);
        } else {
            fp->rx_chain = (struct eth_rx_bd *)fp->rx_dma.vaddr;
        }

        /* link together the rx bd chain pages */
        for (j = 1; j <= RX_BD_NUM_PAGES; j++) {
            /* index into the rx bd chain array to last entry per page */
            struct eth_rx_bd *rx_bd =
                &fp->rx_chain[RX_BD_TOTAL_PER_PAGE * j - 2];
            /* point to the next page and wrap from last page */
            busaddr = (fp->rx_dma.paddr +
                       (BCM_PAGE_SIZE * (j % RX_BD_NUM_PAGES)));
            rx_bd->addr_hi = htole32(U64_HI(busaddr));
            rx_bd->addr_lo = htole32(U64_LO(busaddr));
        }

        /*******************/
        /* FP RX RCQ CHAIN */
        /*******************/

        snprintf(buf, sizeof(buf), "fp %d rcq chain", i);
        if (bxe_dma_alloc(sc, (BCM_PAGE_SIZE * RCQ_NUM_PAGES),
                          &fp->rcq_dma, buf) != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to alloc %s\n", buf);
            return (1);
        } else {
            fp->rcq_chain = (union eth_rx_cqe *)fp->rcq_dma.vaddr;
        }

        /* link together the rcq chain pages */
        for (j = 1; j <= RCQ_NUM_PAGES; j++) {
            /* index into the rcq chain array to last entry per page */
            struct eth_rx_cqe_next_page *rx_cqe_next =
                (struct eth_rx_cqe_next_page *)
                &fp->rcq_chain[RCQ_TOTAL_PER_PAGE * j - 1];
            /* point to the next page and wrap from last page */
            busaddr = (fp->rcq_dma.paddr +
                       (BCM_PAGE_SIZE * (j % RCQ_NUM_PAGES)));
            rx_cqe_next->addr_hi = htole32(U64_HI(busaddr));
            rx_cqe_next->addr_lo = htole32(U64_LO(busaddr));
        }

        /*******************/
        /* FP RX SGE CHAIN */
        /*******************/

        snprintf(buf, sizeof(buf), "fp %d sge chain", i);
        if (bxe_dma_alloc(sc, (BCM_PAGE_SIZE * RX_SGE_NUM_PAGES),
                          &fp->rx_sge_dma, buf) != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to alloc %s\n", buf);
            return (1);
        } else {
            fp->rx_sge_chain = (struct eth_rx_sge *)fp->rx_sge_dma.vaddr;
        }

        /* link together the sge chain pages */
        for (j = 1; j <= RX_SGE_NUM_PAGES; j++) {
            /* index into the rcq chain array to last entry per page */
            struct eth_rx_sge *rx_sge =
                &fp->rx_sge_chain[RX_SGE_TOTAL_PER_PAGE * j - 2];
            /* point to the next page and wrap from last page */
            busaddr = (fp->rx_sge_dma.paddr +
                       (BCM_PAGE_SIZE * (j % RX_SGE_NUM_PAGES)));
            rx_sge->addr_hi = htole32(U64_HI(busaddr));
            rx_sge->addr_lo = htole32(U64_LO(busaddr));
        }

        /***********************/
        /* FP TX MBUF DMA MAPS */
        /***********************/

        /* set required sizes before mapping to conserve resources */
        if (if_getcapenable(sc->ifp) & (IFCAP_TSO4 | IFCAP_TSO6)) {
            max_size     = BXE_TSO_MAX_SIZE;
            max_segments = BXE_TSO_MAX_SEGMENTS;
            max_seg_size = BXE_TSO_MAX_SEG_SIZE;
        } else {
            max_size     = (MCLBYTES * BXE_MAX_SEGMENTS);
            max_segments = BXE_MAX_SEGMENTS;
            max_seg_size = MCLBYTES;
        }

        /* create a dma tag for the tx mbufs */
        rc = bus_dma_tag_create(sc->parent_dma_tag, /* parent tag */
                                1,                  /* alignment */
                                0,                  /* boundary limit */
                                BUS_SPACE_MAXADDR,  /* restricted low */
                                BUS_SPACE_MAXADDR,  /* restricted hi */
                                NULL,               /* addr filter() */
                                NULL,               /* addr filter() arg */
                                max_size,           /* max map size */
                                max_segments,       /* num discontinuous */
                                max_seg_size,       /* max seg size */
                                0,                  /* flags */
                                NULL,               /* lock() */
                                NULL,               /* lock() arg */
                                &fp->tx_mbuf_tag);  /* returned dma tag */
        if (rc != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to create dma tag for "
                      "'fp %d tx mbufs' (%d)\n", i, rc);
            return (1);
        }

        /* create dma maps for each of the tx mbuf clusters */
        for (j = 0; j < TX_BD_TOTAL; j++) {
            if (bus_dmamap_create(fp->tx_mbuf_tag,
                                  BUS_DMA_NOWAIT,
                                  &fp->tx_mbuf_chain[j].m_map)) {
                /* XXX unwind and free previous fastpath allocations */
                BLOGE(sc, "Failed to create dma map for "
                          "'fp %d tx mbuf %d' (%d)\n", i, j, rc);
                return (1);
            }
        }

        /***********************/
        /* FP RX MBUF DMA MAPS */
        /***********************/

        /* create a dma tag for the rx mbufs */
        rc = bus_dma_tag_create(sc->parent_dma_tag, /* parent tag */
                                1,                  /* alignment */
                                0,                  /* boundary limit */
                                BUS_SPACE_MAXADDR,  /* restricted low */
                                BUS_SPACE_MAXADDR,  /* restricted hi */
                                NULL,               /* addr filter() */
                                NULL,               /* addr filter() arg */
                                MJUM9BYTES,         /* max map size */
                                1,                  /* num discontinuous */
                                MJUM9BYTES,         /* max seg size */
                                0,                  /* flags */
                                NULL,               /* lock() */
                                NULL,               /* lock() arg */
                                &fp->rx_mbuf_tag);  /* returned dma tag */
        if (rc != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to create dma tag for "
                      "'fp %d rx mbufs' (%d)\n", i, rc);
            return (1);
        }

        /* create dma maps for each of the rx mbuf clusters */
        for (j = 0; j < RX_BD_TOTAL; j++) {
            if (bus_dmamap_create(fp->rx_mbuf_tag,
                                  BUS_DMA_NOWAIT,
                                  &fp->rx_mbuf_chain[j].m_map)) {
                /* XXX unwind and free previous fastpath allocations */
                BLOGE(sc, "Failed to create dma map for "
                          "'fp %d rx mbuf %d' (%d)\n", i, j, rc);
                return (1);
            }
        }

        /* create dma map for the spare rx mbuf cluster */
        if (bus_dmamap_create(fp->rx_mbuf_tag,
                              BUS_DMA_NOWAIT,
                              &fp->rx_mbuf_spare_map)) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to create dma map for "
                      "'fp %d spare rx mbuf' (%d)\n", i, rc);
            return (1);
        }

        /***************************/
        /* FP RX SGE MBUF DMA MAPS */
        /***************************/

        /* create a dma tag for the rx sge mbufs */
        rc = bus_dma_tag_create(sc->parent_dma_tag, /* parent tag */
                                1,                  /* alignment */
                                0,                  /* boundary limit */
                                BUS_SPACE_MAXADDR,  /* restricted low */
                                BUS_SPACE_MAXADDR,  /* restricted hi */
                                NULL,               /* addr filter() */
                                NULL,               /* addr filter() arg */
                                BCM_PAGE_SIZE,      /* max map size */
                                1,                  /* num discontinuous */
                                BCM_PAGE_SIZE,      /* max seg size */
                                0,                  /* flags */
                                NULL,               /* lock() */
                                NULL,               /* lock() arg */
                                &fp->rx_sge_mbuf_tag); /* returned dma tag */
        if (rc != 0) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to create dma tag for "
                      "'fp %d rx sge mbufs' (%d)\n", i, rc);
            return (1);
        }

        /* create dma maps for the rx sge mbuf clusters */
        for (j = 0; j < RX_SGE_TOTAL; j++) {
            if (bus_dmamap_create(fp->rx_sge_mbuf_tag,
                                  BUS_DMA_NOWAIT,
                                  &fp->rx_sge_mbuf_chain[j].m_map)) {
                /* XXX unwind and free previous fastpath allocations */
                BLOGE(sc, "Failed to create dma map for "
                          "'fp %d rx sge mbuf %d' (%d)\n", i, j, rc);
                return (1);
            }
        }

        /* create dma map for the spare rx sge mbuf cluster */
        if (bus_dmamap_create(fp->rx_sge_mbuf_tag,
                              BUS_DMA_NOWAIT,
                              &fp->rx_sge_mbuf_spare_map)) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to create dma map for "
                      "'fp %d spare rx sge mbuf' (%d)\n", i, rc);
            return (1);
        }

        /***************************/
        /* FP RX TPA MBUF DMA MAPS */
        /***************************/

        /* create dma maps for the rx tpa mbuf clusters */
        max_agg_queues = MAX_AGG_QS(sc);

        for (j = 0; j < max_agg_queues; j++) {
            if (bus_dmamap_create(fp->rx_mbuf_tag,
                                  BUS_DMA_NOWAIT,
                                  &fp->rx_tpa_info[j].bd.m_map)) {
                /* XXX unwind and free previous fastpath allocations */
                BLOGE(sc, "Failed to create dma map for "
                          "'fp %d rx tpa mbuf %d' (%d)\n", i, j, rc);
                return (1);
            }
        }

        /* create dma map for the spare rx tpa mbuf cluster */
        if (bus_dmamap_create(fp->rx_mbuf_tag,
                              BUS_DMA_NOWAIT,
                              &fp->rx_tpa_info_mbuf_spare_map)) {
            /* XXX unwind and free previous fastpath allocations */
            BLOGE(sc, "Failed to create dma map for "
                      "'fp %d spare rx tpa mbuf' (%d)\n", i, rc);
            return (1);
        }

        bxe_init_sge_ring_bit_mask(fp);
    }

    return (0);
}