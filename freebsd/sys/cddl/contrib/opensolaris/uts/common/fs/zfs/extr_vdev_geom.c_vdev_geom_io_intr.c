#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int io_error; scalar_t__ io_type; int /*<<< orphan*/ * io_bio; int /*<<< orphan*/  io_spa; TYPE_3__* io_vd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_7__ {void* vdev_delayed_close; void* vdev_remove_wanted; void* vdev_notrim; void* vdev_nowritecache; } ;
typedef  TYPE_3__ vdev_t ;
struct bio {int bio_error; scalar_t__ bio_resid; TYPE_1__* bio_to; int /*<<< orphan*/  bio_cmd; TYPE_2__* bio_caller1; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
#define  BIO_DELETE 131 
#define  BIO_FLUSH 130 
 void* B_TRUE ; 
 int /*<<< orphan*/  EIO ; 
#define  ENOTSUP 129 
#define  ENXIO 128 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_ASYNC_REMOVE ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  spa_async_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_delay_interrupt (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_geom_io_intr(struct bio *bp)
{
	vdev_t *vd;
	zio_t *zio;

	zio = bp->bio_caller1;
	vd = zio->io_vd;
	zio->io_error = bp->bio_error;
	if (zio->io_error == 0 && bp->bio_resid != 0)
		zio->io_error = SET_ERROR(EIO);

	switch(zio->io_error) {
	case ENOTSUP:
		/*
		 * If we get ENOTSUP for BIO_FLUSH or BIO_DELETE we know
		 * that future attempts will never succeed. In this case
		 * we set a persistent flag so that we don't bother with
		 * requests in the future.
		 */
		switch(bp->bio_cmd) {
		case BIO_FLUSH:
			vd->vdev_nowritecache = B_TRUE;
			break;
		case BIO_DELETE:
			vd->vdev_notrim = B_TRUE;
			break;
		}
		break;
	case ENXIO:
		if (!vd->vdev_remove_wanted) {
			/*
			 * If provider's error is set we assume it is being
			 * removed.
			 */
			if (bp->bio_to->error != 0) {
				vd->vdev_remove_wanted = B_TRUE;
				spa_async_request(zio->io_spa,
				    SPA_ASYNC_REMOVE);
			} else if (!vd->vdev_delayed_close) {
				vd->vdev_delayed_close = B_TRUE;
			}
		}
		break;
	}

	/*
	 * We have to split bio freeing into two parts, because the ABD code
	 * cannot be called in this context and vdev_op_io_done is not called
	 * for ZIO_TYPE_IOCTL zio-s.
	 */
	if (zio->io_type != ZIO_TYPE_READ && zio->io_type != ZIO_TYPE_WRITE) {
		g_destroy_bio(bp);
		zio->io_bio = NULL;
	}
	zio_delay_interrupt(zio);
}