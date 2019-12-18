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
struct mmc_data {int flags; } ;
struct mmc_command {struct mmc_data* data; } ;
struct dwmmc_softc {int /*<<< orphan*/  buf_map; int /*<<< orphan*/  buf_tag; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dma_done(struct dwmmc_softc *sc, struct mmc_command *cmd)
{
	struct mmc_data *data;

	data = cmd->data;

	if (data->flags & MMC_DATA_WRITE)
		bus_dmamap_sync(sc->buf_tag, sc->buf_map,
			BUS_DMASYNC_POSTWRITE);
	else
		bus_dmamap_sync(sc->buf_tag, sc->buf_map,
			BUS_DMASYNC_POSTREAD);

	bus_dmamap_sync(sc->desc_tag, sc->desc_map,
	    BUS_DMASYNC_POSTWRITE);

	bus_dmamap_unload(sc->buf_tag, sc->buf_map);

	return (0);
}