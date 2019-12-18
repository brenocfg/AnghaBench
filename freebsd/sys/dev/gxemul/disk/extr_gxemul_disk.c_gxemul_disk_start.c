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
typedef  int /*<<< orphan*/  uint8_t ;
struct gxemul_disk_softc {int /*<<< orphan*/  sc_dev; } ;
struct bio {int bio_length; int bio_offset; int bio_resid; int bio_cmd; int bio_completed; int /*<<< orphan*/ * bio_data; TYPE_2__* bio_to; } ;
typedef  int off_t ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct gxemul_disk_softc* softc; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int GXEMUL_DISK_DEV_BLOCKSIZE ; 
 unsigned int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  gxemul_disk_controller_mutex ; 
 int gxemul_disk_read (unsigned int,int /*<<< orphan*/ *,int) ; 
 int gxemul_disk_write (unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gxemul_disk_start(struct bio *bp)
{
	struct gxemul_disk_softc *sc;
	unsigned diskid;
	off_t offset;
	uint8_t *buf;
	int error;

	sc = bp->bio_to->geom->softc;
	diskid = device_get_unit(sc->sc_dev);

	if ((bp->bio_length % GXEMUL_DISK_DEV_BLOCKSIZE) != 0) {
		g_io_deliver(bp, EINVAL);
		return;
	}

	buf = bp->bio_data;
	offset = bp->bio_offset;
	bp->bio_resid = bp->bio_length;
	while (bp->bio_resid != 0) {
		switch (bp->bio_cmd) {
		case BIO_READ:
			mtx_lock(&gxemul_disk_controller_mutex);
			error = gxemul_disk_read(diskid, buf, offset);
			mtx_unlock(&gxemul_disk_controller_mutex);
			break;
		case BIO_WRITE:
			mtx_lock(&gxemul_disk_controller_mutex);
			error = gxemul_disk_write(diskid, buf, offset);
			mtx_unlock(&gxemul_disk_controller_mutex);
			break;
		default:
			g_io_deliver(bp, EOPNOTSUPP);
			return;
		}
		if (error != 0) {
			g_io_deliver(bp, error);
			return;
		}

		buf += GXEMUL_DISK_DEV_BLOCKSIZE;
		offset += GXEMUL_DISK_DEV_BLOCKSIZE;
		bp->bio_completed += GXEMUL_DISK_DEV_BLOCKSIZE;
		bp->bio_resid -= GXEMUL_DISK_DEV_BLOCKSIZE;
	}

	g_io_deliver(bp, 0);
}