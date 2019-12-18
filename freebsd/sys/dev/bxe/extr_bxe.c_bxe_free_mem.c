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
struct bxe_softc {TYPE_1__* context; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * vcxt; int /*<<< orphan*/  vcxt_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILT_MEMOP_FREE ; 
 int L2_ILT_LINES (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_dma_free (struct bxe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_free_ilt_lines_mem (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_ilt_mem_op (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_free_mem(struct bxe_softc *sc)
{
    int i;

    for (i = 0; i < L2_ILT_LINES(sc); i++) {
        bxe_dma_free(sc, &sc->context[i].vcxt_dma);
        sc->context[i].vcxt = NULL;
        sc->context[i].size = 0;
    }

    ecore_ilt_mem_op(sc, ILT_MEMOP_FREE);

    bxe_free_ilt_lines_mem(sc);

}