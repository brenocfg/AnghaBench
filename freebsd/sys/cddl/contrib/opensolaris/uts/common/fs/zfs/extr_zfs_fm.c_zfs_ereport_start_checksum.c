#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {unsigned long long zcr_align; struct TYPE_18__* zcr_next; struct TYPE_18__* zcr_ckinfo; int /*<<< orphan*/  zcr_cbinfo; int /*<<< orphan*/  zcr_cbdata; int /*<<< orphan*/  (* zcr_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * zcr_ereport; int /*<<< orphan*/  zcr_detector; int /*<<< orphan*/  zcr_length; } ;
typedef  TYPE_4__ zio_cksum_report_t ;
typedef  int /*<<< orphan*/  zio_bad_cksum_t ;
struct TYPE_19__ {TYPE_2__* vdev_top; } ;
typedef  TYPE_5__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct zio {TYPE_3__* io_logical; TYPE_1__* io_vsd_ops; int /*<<< orphan*/ * io_vsd; } ;
struct TYPE_20__ {int /*<<< orphan*/  spa_errlist_lock; } ;
typedef  TYPE_6__ spa_t ;
struct TYPE_17__ {TYPE_4__* io_cksum_report; } ;
struct TYPE_16__ {unsigned long long vdev_ashift; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* vsd_cksum_report ) (struct zio*,TYPE_4__*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FM_EREPORT_ZFS_CHECKSUM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct zio*,TYPE_4__*,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ereport_start (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*,TYPE_5__*,struct zio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_vsd_default_cksum_report (struct zio*,TYPE_4__*,void*) ; 

void
zfs_ereport_start_checksum(spa_t *spa, vdev_t *vd,
    struct zio *zio, uint64_t offset, uint64_t length, void *arg,
    zio_bad_cksum_t *info)
{
	zio_cksum_report_t *report = kmem_zalloc(sizeof (*report), KM_SLEEP);

	if (zio->io_vsd != NULL)
		zio->io_vsd_ops->vsd_cksum_report(zio, report, arg);
	else
		zio_vsd_default_cksum_report(zio, report, arg);

	/* copy the checksum failure information if it was provided */
	if (info != NULL) {
		report->zcr_ckinfo = kmem_zalloc(sizeof (*info), KM_SLEEP);
		bcopy(info, report->zcr_ckinfo, sizeof (*info));
	}

	report->zcr_align = 1ULL << vd->vdev_top->vdev_ashift;
	report->zcr_length = length;

#ifdef _KERNEL
	zfs_ereport_start(&report->zcr_ereport, &report->zcr_detector,
	    FM_EREPORT_ZFS_CHECKSUM, spa, vd, zio, offset, length);

	if (report->zcr_ereport == NULL) {
		report->zcr_free(report->zcr_cbdata, report->zcr_cbinfo);
		if (report->zcr_ckinfo != NULL) {
			kmem_free(report->zcr_ckinfo,
			    sizeof (*report->zcr_ckinfo));
		}
		kmem_free(report, sizeof (*report));
		return;
	}
#endif

	mutex_enter(&spa->spa_errlist_lock);
	report->zcr_next = zio->io_logical->io_cksum_report;
	zio->io_logical->io_cksum_report = report;
	mutex_exit(&spa->spa_errlist_lock);
}