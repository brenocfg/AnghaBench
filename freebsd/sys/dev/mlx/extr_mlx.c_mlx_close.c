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
struct thread {int dummy; } ;
struct mlx_softc {int /*<<< orphan*/  mlx_state; } ;
struct cdev {struct mlx_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CONFIG_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_CONFIG_UNLOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_STATE_OPEN ; 

int
mlx_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
    struct mlx_softc	*sc = dev->si_drv1;

    MLX_CONFIG_LOCK(sc);
    MLX_IO_LOCK(sc);
    sc->mlx_state &= ~MLX_STATE_OPEN;
    MLX_IO_UNLOCK(sc);
    MLX_CONFIG_UNLOCK(sc);
    return (0);
}