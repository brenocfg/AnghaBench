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
struct mlx_softc {int /*<<< orphan*/  mlx_buffer_dmat; int /*<<< orphan*/  mlx_freecmds; } ;
struct mlx_command {int /*<<< orphan*/  mc_dmamap; struct mlx_softc* mc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct mlx_command* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mlx_command*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (struct mlx_command*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mc_link ; 

__attribute__((used)) static struct mlx_command *
mlx_alloccmd(struct mlx_softc *sc)
{
    struct mlx_command	*mc;
    int			error;

    debug_called(1);

    MLX_IO_ASSERT_LOCKED(sc);
    if ((mc = TAILQ_FIRST(&sc->mlx_freecmds)) != NULL)
	TAILQ_REMOVE(&sc->mlx_freecmds, mc, mc_link);

    /* allocate a new command buffer? */
    if (mc == NULL) {
	mc = (struct mlx_command *)malloc(sizeof(*mc), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mc != NULL) {
	    mc->mc_sc = sc;
	    error = bus_dmamap_create(sc->mlx_buffer_dmat, 0, &mc->mc_dmamap);
	    if (error) {
		free(mc, M_DEVBUF);
		return(NULL);
	    }
	}
    }
    return(mc);
}