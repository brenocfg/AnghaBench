#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxd_softc {int /*<<< orphan*/  mlxd_controller; TYPE_1__* mlxd_drive; } ;
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; TYPE_2__* bio_disk; } ;
struct TYPE_4__ {struct mlxd_softc* d_drv1; } ;
struct TYPE_3__ {scalar_t__ ms_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  MLX_IO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ MLX_SYSD_OFFLINE ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mlx_submit_buf (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static void
mlxd_strategy(struct bio *bp)
{
    struct mlxd_softc	*sc = bp->bio_disk->d_drv1;

    debug_called(1);

    /* bogus disk? */
    if (sc == NULL) {
	bp->bio_error = EINVAL;
	bp->bio_flags |= BIO_ERROR;
	goto bad;
    }

    /* XXX may only be temporarily offline - sleep? */
    MLX_IO_LOCK(sc->mlxd_controller);
    if (sc->mlxd_drive->ms_state == MLX_SYSD_OFFLINE) {
	MLX_IO_UNLOCK(sc->mlxd_controller);
	bp->bio_error = ENXIO;
	bp->bio_flags |= BIO_ERROR;
	goto bad;
    }

    mlx_submit_buf(sc->mlxd_controller, bp);
    MLX_IO_UNLOCK(sc->mlxd_controller);
    return;

 bad:
    /*
     * Correctly set the bio to indicate a failed transfer.
     */
    bp->bio_resid = bp->bio_bcount;
    biodone(bp);
    return;
}