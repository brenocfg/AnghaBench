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
struct mrsas_softc {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  data_tag; } ;
struct mrsas_mpt_cmd {int flags; int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int MRSAS_DIR_IN ; 
 int MRSAS_DIR_OUT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
mrsas_unmap_request(struct mrsas_softc *sc, struct mrsas_mpt_cmd *cmd)
{
	if (cmd->data != NULL) {
		if (cmd->flags & MRSAS_DIR_IN)
			bus_dmamap_sync(sc->data_tag, cmd->data_dmamap, BUS_DMASYNC_POSTREAD);
		if (cmd->flags & MRSAS_DIR_OUT)
			bus_dmamap_sync(sc->data_tag, cmd->data_dmamap, BUS_DMASYNC_POSTWRITE);
		mtx_lock(&sc->io_lock);
		bus_dmamap_unload(sc->data_tag, cmd->data_dmamap);
		mtx_unlock(&sc->io_lock);
	}
}