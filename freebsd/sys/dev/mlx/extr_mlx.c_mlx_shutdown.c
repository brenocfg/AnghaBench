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
struct mlx_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CONFIG_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_CONFIG_UNLOCK (struct mlx_softc*) ; 
 struct mlx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mlx_shutdown_locked (struct mlx_softc*) ; 

int
mlx_shutdown(device_t dev)
{
    struct mlx_softc	*sc = device_get_softc(dev);
    int			error;

    MLX_CONFIG_LOCK(sc);
    error = mlx_shutdown_locked(sc);
    MLX_CONFIG_UNLOCK(sc);
    return (error);
}