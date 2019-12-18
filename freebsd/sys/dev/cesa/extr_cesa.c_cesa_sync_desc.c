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
struct cesa_softc {int /*<<< orphan*/  sc_requests_cdm; int /*<<< orphan*/  sc_sdesc_cdm; int /*<<< orphan*/  sc_tdesc_cdm; } ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  cesa_sync_dma_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cesa_sync_desc(struct cesa_softc *sc, bus_dmasync_op_t op)
{

	cesa_sync_dma_mem(&sc->sc_tdesc_cdm, op);
	cesa_sync_dma_mem(&sc->sc_sdesc_cdm, op);
	cesa_sync_dma_mem(&sc->sc_requests_cdm, op);
}