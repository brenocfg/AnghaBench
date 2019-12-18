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
struct mlx_softc {int mlx_state; int /*<<< orphan*/  mlx_buffer_dmat; int /*<<< orphan*/  mlx_waitbufs; int /*<<< orphan*/  mlx_bioq; } ;
struct mlx_command {int /*<<< orphan*/  mc_length; int /*<<< orphan*/  mc_data; int /*<<< orphan*/  mc_dmamap; struct bio* mc_private; int /*<<< orphan*/  mc_complete; } ;
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_data; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int MLX_STATE_QFROZEN ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx_command*,int /*<<< orphan*/ ) ; 
 struct mlx_command* mlx_alloccmd (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_completeio ; 
 scalar_t__ mlx_getslot (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_startio_cb ; 

__attribute__((used)) static void
mlx_startio(struct mlx_softc *sc)
{
    struct mlx_command	*mc;
    struct bio		*bp;
    int			error;

    MLX_IO_ASSERT_LOCKED(sc);

    /* spin until something prevents us from doing any work */
    for (;;) {
	if (sc->mlx_state & MLX_STATE_QFROZEN)
	    break;

	/* see if there's work to be done */
	if ((bp = bioq_first(&sc->mlx_bioq)) == NULL)
	    break;
	/* get a command */
	if ((mc = mlx_alloccmd(sc)) == NULL)
	    break;
	/* get a slot for the command */
	if (mlx_getslot(mc) != 0) {
	    mlx_releasecmd(mc);
	    break;
	}
	/* get the buf containing our work */
	bioq_remove(&sc->mlx_bioq, bp);
	sc->mlx_waitbufs--;
	
	/* connect the buf to the command */
	mc->mc_complete = mlx_completeio;
	mc->mc_private = bp;
	mc->mc_data = bp->bio_data;
	mc->mc_length = bp->bio_bcount;
	
	/* map the command so the controller can work with it */
	error = bus_dmamap_load(sc->mlx_buffer_dmat, mc->mc_dmamap, mc->mc_data,
				mc->mc_length, mlx_startio_cb, mc, 0);
	if (error == EINPROGRESS) {
	    sc->mlx_state |= MLX_STATE_QFROZEN;
	    break;
	}
    }
}