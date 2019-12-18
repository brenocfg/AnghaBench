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
struct mly_softc {int /*<<< orphan*/  mly_buffer_dmat; } ;
struct mly_command {int mc_flags; int /*<<< orphan*/  mc_datamap; int /*<<< orphan*/  mc_length; int /*<<< orphan*/ * mc_data; struct mly_softc* mc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int MLY_CMD_CCB ; 
 int MLY_CMD_DATAIN ; 
 int MLY_CMD_DATAOUT ; 
 int MLY_CMD_MAPPED ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mly_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mly_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_map_command_sg ; 

__attribute__((used)) static void
mly_map_command(struct mly_command *mc)
{
    struct mly_softc	*sc = mc->mc_sc;

    debug_called(2);

    /* don't map more than once */
    if (mc->mc_flags & MLY_CMD_MAPPED)
	return;

    /* does the command have a data buffer? */
    if (mc->mc_data != NULL) {
	if (mc->mc_flags & MLY_CMD_CCB)
		bus_dmamap_load_ccb(sc->mly_buffer_dmat, mc->mc_datamap,
				mc->mc_data, mly_map_command_sg, mc, 0);
	else 
		bus_dmamap_load(sc->mly_buffer_dmat, mc->mc_datamap,
				mc->mc_data, mc->mc_length, 
				mly_map_command_sg, mc, 0);
	if (mc->mc_flags & MLY_CMD_DATAIN)
	    bus_dmamap_sync(sc->mly_buffer_dmat, mc->mc_datamap, BUS_DMASYNC_PREREAD);
	if (mc->mc_flags & MLY_CMD_DATAOUT)
	    bus_dmamap_sync(sc->mly_buffer_dmat, mc->mc_datamap, BUS_DMASYNC_PREWRITE);
    }
    mc->mc_flags |= MLY_CMD_MAPPED;
}