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
struct mlx_softc {int /*<<< orphan*/  mlx_buffer_dmat; } ;
struct mlx_command {int mc_flags; int /*<<< orphan*/  mc_dmamap; int /*<<< orphan*/ * mc_data; struct mlx_softc* mc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int MLX_CMD_DATAIN ; 
 int MLX_CMD_DATAOUT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
mlx_unmapcmd(struct mlx_command *mc)
{
    struct mlx_softc	*sc = mc->mc_sc;

    debug_called(1);

    /* if the command involved data at all */
    if (mc->mc_data != NULL) {
	
	if (mc->mc_flags & MLX_CMD_DATAIN)
	    bus_dmamap_sync(sc->mlx_buffer_dmat, mc->mc_dmamap, BUS_DMASYNC_POSTREAD);
	if (mc->mc_flags & MLX_CMD_DATAOUT)
	    bus_dmamap_sync(sc->mlx_buffer_dmat, mc->mc_dmamap, BUS_DMASYNC_POSTWRITE);

	bus_dmamap_unload(sc->mlx_buffer_dmat, mc->mc_dmamap); 
    }
}