#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ io_done; TYPE_1__* io_vd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_14__ {int /*<<< orphan*/  vq_lock; int /*<<< orphan*/  vq_io_complete_ts; } ;
typedef  TYPE_3__ vdev_queue_t ;
struct TYPE_12__ {TYPE_3__ vdev_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_queue_agg_io_done ; 
 TYPE_2__* vdev_queue_io_to_issue (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_queue_pending_remove (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_execute (TYPE_2__*) ; 
 int /*<<< orphan*/  zio_nowait (TYPE_2__*) ; 
 int /*<<< orphan*/  zio_vdev_io_reissue (TYPE_2__*) ; 

void
vdev_queue_io_done(zio_t *zio)
{
	vdev_queue_t *vq = &zio->io_vd->vdev_queue;
	zio_t *nio;

	mutex_enter(&vq->vq_lock);

	vdev_queue_pending_remove(vq, zio);

	vq->vq_io_complete_ts = gethrtime();

	while ((nio = vdev_queue_io_to_issue(vq)) != NULL) {
		mutex_exit(&vq->vq_lock);
		if (nio->io_done == vdev_queue_agg_io_done) {
			zio_nowait(nio);
		} else {
			zio_vdev_io_reissue(nio);
			zio_execute(nio);
		}
		mutex_enter(&vq->vq_lock);
	}

	mutex_exit(&vq->vq_lock);
}