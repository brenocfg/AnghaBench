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
struct TYPE_2__ {int zv_state; int /*<<< orphan*/  zv_zilog; int /*<<< orphan*/  zv_queue_mtx; int /*<<< orphan*/  zv_queue; } ;
typedef  TYPE_1__ zvol_state_t ;
struct bio {int bio_cmd; } ;

/* Variables and functions */
#define  BIO_DELETE 131 
#define  BIO_FLUSH 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int*) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_strategy (struct bio*) ; 

__attribute__((used)) static void
zvol_geom_worker(void *arg)
{
	zvol_state_t *zv;
	struct bio *bp;

	thread_lock(curthread);
	sched_prio(curthread, PRIBIO);
	thread_unlock(curthread);

	zv = arg;
	for (;;) {
		mtx_lock(&zv->zv_queue_mtx);
		bp = bioq_takefirst(&zv->zv_queue);
		if (bp == NULL) {
			if (zv->zv_state == 1) {
				zv->zv_state = 2;
				wakeup(&zv->zv_state);
				mtx_unlock(&zv->zv_queue_mtx);
				kthread_exit();
			}
			msleep(&zv->zv_queue, &zv->zv_queue_mtx, PRIBIO | PDROP,
			    "zvol:io", 0);
			continue;
		}
		mtx_unlock(&zv->zv_queue_mtx);
		switch (bp->bio_cmd) {
		case BIO_FLUSH:
			zil_commit(zv->zv_zilog, ZVOL_OBJ);
			g_io_deliver(bp, 0);
			break;
		case BIO_READ:
		case BIO_WRITE:
		case BIO_DELETE:
			zvol_strategy(bp);
			break;
		default:
			g_io_deliver(bp, EOPNOTSUPP);
			break;
		}
	}
}