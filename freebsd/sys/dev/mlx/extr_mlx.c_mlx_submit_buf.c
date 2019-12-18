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
struct mlx_softc {int /*<<< orphan*/  mlx_waitbufs; int /*<<< orphan*/  mlx_bioq; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mlx_startio (struct mlx_softc*) ; 

int
mlx_submit_buf(struct mlx_softc *sc, struct bio *bp)
{
    
    debug_called(1);

    MLX_IO_ASSERT_LOCKED(sc);
    bioq_insert_tail(&sc->mlx_bioq, bp);
    sc->mlx_waitbufs++;
    mlx_startio(sc);
    return(0);
}