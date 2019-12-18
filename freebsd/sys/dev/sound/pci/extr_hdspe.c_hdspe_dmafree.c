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
struct sc_info {int /*<<< orphan*/ * pbuf; int /*<<< orphan*/ * rbuf; int /*<<< orphan*/  pmap; int /*<<< orphan*/  dmat; int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdspe_dmafree(struct sc_info *sc)
{

	bus_dmamap_unload(sc->dmat, sc->rmap);
	bus_dmamap_unload(sc->dmat, sc->pmap);
	bus_dmamem_free(sc->dmat, sc->rbuf, sc->rmap);
	bus_dmamem_free(sc->dmat, sc->pbuf, sc->pmap);
	sc->rbuf = sc->pbuf = NULL;
}