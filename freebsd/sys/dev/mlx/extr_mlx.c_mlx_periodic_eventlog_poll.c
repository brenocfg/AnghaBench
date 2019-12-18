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
struct mlx_command {int mc_length; int /*<<< orphan*/ * mc_data; int /*<<< orphan*/  mc_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct mlx_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx_command* mlx_alloccmd (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_eventlog_cb ; 
 scalar_t__ mlx_getslot (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 

__attribute__((used)) static void
mlx_periodic_eventlog_poll(struct mlx_softc *sc)
{
    struct mlx_command	*mc;
    void		*result = NULL;
    int			error = 0;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    /* get ourselves a command buffer */
    error = 1;
    if ((mc = mlx_alloccmd(sc)) == NULL)
	goto out;

    /* allocate the response structure */
    if ((result = malloc(/*sizeof(struct mlx_eventlog_entry)*/1024, M_DEVBUF,
			 M_NOWAIT)) == NULL)
	goto out;

    /* get a command slot */
    if (mlx_getslot(mc))
	goto out;

    /* map the command so the controller can see it */
    mc->mc_data = result;
    mc->mc_length = /*sizeof(struct mlx_eventlog_entry)*/1024;
    error = bus_dmamap_load(sc->mlx_buffer_dmat, mc->mc_dmamap, mc->mc_data,
			    mc->mc_length, mlx_eventlog_cb, mc, BUS_DMA_NOWAIT);

 out:
    if (error != 0) {
	if (mc != NULL)
	    mlx_releasecmd(mc);
	if ((result != NULL) && (mc->mc_data != NULL))
	    free(result, M_DEVBUF);
    }
}