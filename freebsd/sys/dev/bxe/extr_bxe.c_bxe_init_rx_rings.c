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
struct bxe_softc {int num_queues; struct bxe_fastpath* fp; } ;
struct TYPE_2__ {int /*<<< orphan*/  paddr; } ;
struct bxe_fastpath {TYPE_1__ rcq_dma; int /*<<< orphan*/  rx_sge_prod; int /*<<< orphan*/  rx_cq_prod; int /*<<< orphan*/  rx_bd_prod; scalar_t__ rx_bd_cons; } ;

/* Variables and functions */
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_MEM_WORKAROUND_ADDRESS_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_update_rx_prod (struct bxe_softc*,struct bxe_fastpath*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_init_rx_rings(struct bxe_softc *sc)
{
    struct bxe_fastpath *fp;
    int i;

    for (i = 0; i < sc->num_queues; i++) {
        fp = &sc->fp[i];

        fp->rx_bd_cons = 0;

        /*
         * Activate the BD ring...
         * Warning, this will generate an interrupt (to the TSTORM)
         * so this can only be done after the chip is initialized
         */
        bxe_update_rx_prod(sc, fp,
                           fp->rx_bd_prod,
                           fp->rx_cq_prod,
                           fp->rx_sge_prod);

        if (i != 0) {
            continue;
        }

        if (CHIP_IS_E1(sc)) {
            REG_WR(sc,
                   (BAR_USTRORM_INTMEM +
                    USTORM_MEM_WORKAROUND_ADDRESS_OFFSET(SC_FUNC(sc))),
                   U64_LO(fp->rcq_dma.paddr));
            REG_WR(sc,
                   (BAR_USTRORM_INTMEM +
                    USTORM_MEM_WORKAROUND_ADDRESS_OFFSET(SC_FUNC(sc)) + 4),
                   U64_HI(fp->rcq_dma.paddr));
        }
    }
}