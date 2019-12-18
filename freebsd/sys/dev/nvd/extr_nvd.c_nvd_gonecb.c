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
struct nvd_disk {int /*<<< orphan*/  bioqlock; int /*<<< orphan*/  tq; TYPE_1__* ctrlr; int /*<<< orphan*/  disk; } ;
struct disk {scalar_t__ d_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NVD ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nvd_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrlr_tailq ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_head ; 
 int /*<<< orphan*/  free (struct nvd_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_tailq ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvd_lock ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvd_gonecb(struct disk *dp)
{
	struct nvd_disk *ndisk = (struct nvd_disk *)dp->d_drv1;

	disk_destroy(ndisk->disk);
	mtx_lock(&nvd_lock);
	TAILQ_REMOVE(&disk_head, ndisk, global_tailq);
	TAILQ_REMOVE(&ndisk->ctrlr->disk_head, ndisk, ctrlr_tailq);
	if (TAILQ_EMPTY(&ndisk->ctrlr->disk_head))
		wakeup(&ndisk->ctrlr->disk_head);
	mtx_unlock(&nvd_lock);
	taskqueue_free(ndisk->tq);
	mtx_destroy(&ndisk->bioqlock);
	free(ndisk, M_NVD);
}