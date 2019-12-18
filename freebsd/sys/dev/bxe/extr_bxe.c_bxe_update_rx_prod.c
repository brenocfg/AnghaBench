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
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct ustorm_eth_rx_producers {void* sge_prod; void* cqe_prod; void* bd_prod; int /*<<< orphan*/  member_0; } ;
struct bxe_softc {int dummy; } ;
struct bxe_fastpath {int /*<<< orphan*/  index; scalar_t__ ustorm_rx_prods_offset; } ;
typedef  int /*<<< orphan*/  rx_prods ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,void*,void*) ; 
 int /*<<< orphan*/  DBG_RX ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
bxe_update_rx_prod(struct bxe_softc    *sc,
                   struct bxe_fastpath *fp,
                   uint16_t            rx_bd_prod,
                   uint16_t            rx_cq_prod,
                   uint16_t            rx_sge_prod)
{
    struct ustorm_eth_rx_producers rx_prods = { 0 };
    uint32_t i;

    /* update producers */
    rx_prods.bd_prod  = rx_bd_prod;
    rx_prods.cqe_prod = rx_cq_prod;
    rx_prods.sge_prod = rx_sge_prod;

    /*
     * Make sure that the BD and SGE data is updated before updating the
     * producers since FW might read the BD/SGE right after the producer
     * is updated.
     * This is only applicable for weak-ordered memory model archs such
     * as IA-64. The following barrier is also mandatory since FW will
     * assumes BDs must have buffers.
     */
    wmb();

    for (i = 0; i < (sizeof(rx_prods) / 4); i++) {
        REG_WR(sc,
               (fp->ustorm_rx_prods_offset + (i * 4)),
               ((uint32_t *)&rx_prods)[i]);
    }

    wmb(); /* keep prod updates ordered */

    BLOGD(sc, DBG_RX,
          "RX fp[%d]: wrote prods bd_prod=%u cqe_prod=%u sge_prod=%u\n",
          fp->index, rx_bd_prod, rx_cq_prod, rx_sge_prod);
}