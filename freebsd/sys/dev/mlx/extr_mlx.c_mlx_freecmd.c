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
struct mlx_command {int /*<<< orphan*/  mc_dmamap; struct mlx_softc* mc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (struct mlx_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx_freecmd(struct mlx_command *mc) 
{
    struct mlx_softc	*sc = mc->mc_sc;
    
    debug_called(1);
    bus_dmamap_destroy(sc->mlx_buffer_dmat, mc->mc_dmamap);
    free(mc, M_DEVBUF);
}