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
struct TYPE_4__ {int /*<<< orphan*/  zv_queue; int /*<<< orphan*/  zv_queue_mtx; int /*<<< orphan*/  zv_objset; int /*<<< orphan*/  zv_zilog; } ;
typedef  TYPE_2__ zvol_state_t ;
typedef  int uint64_t ;
struct bio {int bio_cmd; int /*<<< orphan*/  bio_attribute; TYPE_1__* bio_to; } ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int boolean_t ;
struct TYPE_3__ {TYPE_2__* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  THREAD_CAN_SLEEP () ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int /*<<< orphan*/ * bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/ * dmu_objset_spa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_space (int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  g_handleattr_int (struct bio*,char*,int) ; 
 int /*<<< orphan*/  g_handleattr_off_t (struct bio*,char*,int) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int metaslab_class_get_alloc (int /*<<< orphan*/ ) ; 
 int metaslab_class_get_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_normal_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_strategy (struct bio*) ; 

__attribute__((used)) static void
zvol_geom_start(struct bio *bp)
{
	zvol_state_t *zv;
	boolean_t first;

	zv = bp->bio_to->private;
	ASSERT(zv != NULL);
	switch (bp->bio_cmd) {
	case BIO_FLUSH:
		if (!THREAD_CAN_SLEEP())
			goto enqueue;
		zil_commit(zv->zv_zilog, ZVOL_OBJ);
		g_io_deliver(bp, 0);
		break;
	case BIO_READ:
	case BIO_WRITE:
	case BIO_DELETE:
		if (!THREAD_CAN_SLEEP())
			goto enqueue;
		zvol_strategy(bp);
		break;
	case BIO_GETATTR: {
		spa_t *spa = dmu_objset_spa(zv->zv_objset);
		uint64_t refd, avail, usedobjs, availobjs, val;

		if (g_handleattr_int(bp, "GEOM::candelete", 1))
			return;
		if (strcmp(bp->bio_attribute, "blocksavail") == 0) {
			dmu_objset_space(zv->zv_objset, &refd, &avail,
			    &usedobjs, &availobjs);
			if (g_handleattr_off_t(bp, "blocksavail",
			    avail / DEV_BSIZE))
				return;
		} else if (strcmp(bp->bio_attribute, "blocksused") == 0) {
			dmu_objset_space(zv->zv_objset, &refd, &avail,
			    &usedobjs, &availobjs);
			if (g_handleattr_off_t(bp, "blocksused",
			    refd / DEV_BSIZE))
				return;
		} else if (strcmp(bp->bio_attribute, "poolblocksavail") == 0) {
			avail = metaslab_class_get_space(spa_normal_class(spa));
			avail -= metaslab_class_get_alloc(spa_normal_class(spa));
			if (g_handleattr_off_t(bp, "poolblocksavail",
			    avail / DEV_BSIZE))
				return;
		} else if (strcmp(bp->bio_attribute, "poolblocksused") == 0) {
			refd = metaslab_class_get_alloc(spa_normal_class(spa));
			if (g_handleattr_off_t(bp, "poolblocksused",
			    refd / DEV_BSIZE))
				return;
		}
		/* FALLTHROUGH */
	}
	default:
		g_io_deliver(bp, EOPNOTSUPP);
		break;
	}
	return;

enqueue:
	mtx_lock(&zv->zv_queue_mtx);
	first = (bioq_first(&zv->zv_queue) == NULL);
	bioq_insert_tail(&zv->zv_queue, bp);
	mtx_unlock(&zv->zv_queue_mtx);
	if (first)
		wakeup_one(&zv->zv_queue);
}