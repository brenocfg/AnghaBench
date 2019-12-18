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
struct fdc_data {int /*<<< orphan*/  fdc_mtx; int /*<<< orphan*/  head; } ;
struct fd_data {int flags; int /*<<< orphan*/  fd_bq; int /*<<< orphan*/  toffhandle; int /*<<< orphan*/  fd_iocount; struct fdc_data* fdc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int FD_MOTOR ; 
 int FD_MOTORWAIT ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_motor (struct fd_data*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fd_enqueue(struct fd_data *fd, struct bio *bp)
{
	struct fdc_data *fdc;
	int call;

	call = 0;
	fdc = fd->fdc;
	mtx_lock(&fdc->fdc_mtx);
	/* If we go from idle, cancel motor turnoff */
	if (fd->fd_iocount++ == 0)
		callout_stop(&fd->toffhandle);
	if (fd->flags & FD_MOTOR) {
		/* The motor is on, send it directly to the controller */
		bioq_disksort(&fdc->head, bp);
		wakeup(&fdc->head);
	} else {
		/* Queue it on the drive until the motor has started */
		bioq_insert_tail(&fd->fd_bq, bp);
		if (!(fd->flags & FD_MOTORWAIT))
			fd_motor(fd, 1);
	}
	mtx_unlock(&fdc->fdc_mtx);
}