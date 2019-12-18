#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx_softc {TYPE_1__* mlx_sysdrive; int /*<<< orphan*/  mlx_dev; int /*<<< orphan*/  (* mlx_intaction ) (struct mlx_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mlx_state; } ;
struct TYPE_2__ {scalar_t__ ms_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CONFIG_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_INTACTION_DISABLE ; 
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int MLX_MAXDRIVES ; 
 int /*<<< orphan*/  MLX_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mlx_flush (struct mlx_softc*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (struct mlx_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx_shutdown_locked(struct mlx_softc *sc)
{
    int			i, error;

    debug_called(1);

    MLX_CONFIG_ASSERT_LOCKED(sc);

    MLX_IO_LOCK(sc);
    sc->mlx_state |= MLX_STATE_SHUTDOWN;
    sc->mlx_intaction(sc, MLX_INTACTION_DISABLE);

    /* flush controller */
    device_printf(sc->mlx_dev, "flushing cache...");
    if (mlx_flush(sc)) {
	printf("failed\n");
    } else {
	printf("done\n");
    }
    MLX_IO_UNLOCK(sc);
    
    /* delete all our child devices */
    for (i = 0; i < MLX_MAXDRIVES; i++) {
	if (sc->mlx_sysdrive[i].ms_disk != 0) {
	    if ((error = device_delete_child(sc->mlx_dev, sc->mlx_sysdrive[i].ms_disk)) != 0)
		return (error);
	    sc->mlx_sysdrive[i].ms_disk = 0;
	}
    }

    return (0);
}