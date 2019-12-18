#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlxd_softc {TYPE_1__* mlxd_controller; int /*<<< orphan*/  mlxd_flags; } ;
struct disk {scalar_t__ d_drv1; } ;
struct TYPE_5__ {int mlx_state; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MLXD_OPEN ; 
 int /*<<< orphan*/  MLX_CONFIG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MLX_CONFIG_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MLX_IO_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (TYPE_1__*) ; 
 int MLX_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
mlxd_open(struct disk *dp)
{
    struct mlxd_softc	*sc = (struct mlxd_softc *)dp->d_drv1;

    debug_called(1);
	
    if (sc == NULL)
	return (ENXIO);

    /* controller not active? */
    MLX_CONFIG_LOCK(sc->mlxd_controller);
    MLX_IO_LOCK(sc->mlxd_controller);
    if (sc->mlxd_controller->mlx_state & MLX_STATE_SHUTDOWN) {
	MLX_IO_UNLOCK(sc->mlxd_controller);
	MLX_CONFIG_UNLOCK(sc->mlxd_controller);
	return(ENXIO);
    }

    sc->mlxd_flags |= MLXD_OPEN;
    MLX_IO_UNLOCK(sc->mlxd_controller);
    MLX_CONFIG_UNLOCK(sc->mlxd_controller);
    return (0);
}