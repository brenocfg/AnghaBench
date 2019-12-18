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

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mlx_done (struct mlx_softc*,int) ; 

void
mlx_intr(void *arg)
{
    struct mlx_softc	*sc = (struct mlx_softc *)arg;

    debug_called(1);

    /* collect finished commands, queue anything waiting */
    MLX_IO_LOCK(sc);
    mlx_done(sc, 1);
    MLX_IO_UNLOCK(sc);
}