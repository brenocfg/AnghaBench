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
struct mlxd_softc {int /*<<< orphan*/  mlxd_controller; int /*<<< orphan*/  mlxd_flags; } ;
struct disk {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MLXD_OPEN ; 
 int /*<<< orphan*/  MLX_CONFIG_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_CONFIG_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_IO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
mlxd_close(struct disk *dp)
{
    struct mlxd_softc	*sc = (struct mlxd_softc *)dp->d_drv1;

    debug_called(1);

    if (sc == NULL)
	return (ENXIO);
    MLX_CONFIG_LOCK(sc->mlxd_controller);
    MLX_IO_LOCK(sc->mlxd_controller);
    sc->mlxd_flags &= ~MLXD_OPEN;
    MLX_IO_UNLOCK(sc->mlxd_controller);
    MLX_CONFIG_UNLOCK(sc->mlxd_controller);
    return (0);
}