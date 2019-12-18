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
struct mlxd_softc {int mlxd_flags; } ;
struct mlx_softc {int mlx_state; TYPE_1__* mlx_sysdrive; } ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {scalar_t__ ms_disk; } ;

/* Variables and functions */
 int EBUSY ; 
 int MLXD_OPEN ; 
 int /*<<< orphan*/  MLX_CONFIG_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_CONFIG_UNLOCK (struct mlx_softc*) ; 
 int MLX_MAXDRIVES ; 
 int MLX_STATE_OPEN ; 
 int /*<<< orphan*/  debug_called (int) ; 
 void* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  mlx_free (struct mlx_softc*) ; 
 int mlx_shutdown (scalar_t__) ; 

int
mlx_detach(device_t dev)
{
    struct mlx_softc	*sc = device_get_softc(dev);
    struct mlxd_softc	*mlxd;
    int			i, error;

    debug_called(1);

    error = EBUSY;
    MLX_CONFIG_LOCK(sc);
    if (sc->mlx_state & MLX_STATE_OPEN)
	goto out;

    for (i = 0; i < MLX_MAXDRIVES; i++) {
	if (sc->mlx_sysdrive[i].ms_disk != 0) {
	    mlxd = device_get_softc(sc->mlx_sysdrive[i].ms_disk);
	    if (mlxd->mlxd_flags & MLXD_OPEN) {		/* drive is mounted, abort detach */
		device_printf(sc->mlx_sysdrive[i].ms_disk, "still open, can't detach\n");
		goto out;
	    }
	}
    }
    if ((error = mlx_shutdown(dev)))
	goto out;
    MLX_CONFIG_UNLOCK(sc);

    mlx_free(sc);

    return (0);
 out:
    MLX_CONFIG_UNLOCK(sc);
    return(error);
}