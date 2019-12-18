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
struct mlx_softc {int /*<<< orphan*/  (* mlx_intaction ) (struct mlx_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mlx_dev; int /*<<< orphan*/  mlx_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_INTACTION_DISABLE ; 
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_STATE_SUSPEND ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct mlx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mlx_flush (struct mlx_softc*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct mlx_softc*,int /*<<< orphan*/ ) ; 

int
mlx_suspend(device_t dev)
{
    struct mlx_softc	*sc = device_get_softc(dev);

    debug_called(1);

    MLX_IO_LOCK(sc);
    sc->mlx_state |= MLX_STATE_SUSPEND;
    
    /* flush controller */
    device_printf(sc->mlx_dev, "flushing cache...");
    printf("%s\n", mlx_flush(sc) ? "failed" : "done");

    sc->mlx_intaction(sc, MLX_INTACTION_DISABLE);
    MLX_IO_UNLOCK(sc);

    return(0);
}