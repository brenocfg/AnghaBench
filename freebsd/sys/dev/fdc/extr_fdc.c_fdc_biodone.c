#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fdc_data {int /*<<< orphan*/  fdc_mtx; struct fd_data* fd; struct bio* bp; } ;
struct fd_data {scalar_t__ fd_iocount; TYPE_1__* fdc; int /*<<< orphan*/  toffhandle; } ;
struct bio {int bio_error; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/ * bio_to; } ;
struct TYPE_2__ {scalar_t__ retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_DONE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct fd_data*) ; 
 int debugflags ; 
 int /*<<< orphan*/  fd_turnoff ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (struct bio*) ; 

__attribute__((used)) static int
fdc_biodone(struct fdc_data *fdc, int error)
{
	struct fd_data *fd;
	struct bio *bp;

	fd = fdc->fd;
	bp = fdc->bp;

	mtx_lock(&fdc->fdc_mtx);
	if (--fd->fd_iocount == 0)
		callout_reset(&fd->toffhandle, 4 * hz, fd_turnoff, fd);
	fdc->bp = NULL;
	fdc->fd = NULL;
	mtx_unlock(&fdc->fdc_mtx);
	if (bp->bio_to != NULL) {
		if ((debugflags & 2) && fd->fdc->retry > 0)
			printf("retries: %d\n", fd->fdc->retry);
		g_io_deliver(bp, error);
		return (0);
	}
	bp->bio_error = error;
	bp->bio_flags |= BIO_DONE;
	wakeup(bp);
	return (0);
}