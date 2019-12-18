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
struct TYPE_13__ {int zs_atime; int /*<<< orphan*/  zs_lock; void* zs_ipf_blkid; void* zs_pf_blkid; void* zs_blkid; } ;
typedef  TYPE_2__ zstream_t ;
struct TYPE_14__ {int /*<<< orphan*/  zf_stream; TYPE_1__* zf_dnode; int /*<<< orphan*/  zf_rwlock; } ;
typedef  TYPE_3__ zfetch_t ;
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int dn_maxblkid; int dn_datablksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int NANOSEC ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFETCHSTAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_zfetch_stream_remove (TYPE_3__*,TYPE_2__*) ; 
 int gethrtime () ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfetch_max_distance ; 
 int /*<<< orphan*/  zfetch_max_streams ; 
 int zfetch_min_sec_reap ; 
 int /*<<< orphan*/  zfetchstat_max_streams ; 

__attribute__((used)) static void
dmu_zfetch_stream_create(zfetch_t *zf, uint64_t blkid)
{
	zstream_t *zs_next;
	int numstreams = 0;

	ASSERT(RW_WRITE_HELD(&zf->zf_rwlock));

	/*
	 * Clean up old streams.
	 */
	for (zstream_t *zs = list_head(&zf->zf_stream);
	    zs != NULL; zs = zs_next) {
		zs_next = list_next(&zf->zf_stream, zs);
		if (((gethrtime() - zs->zs_atime) / NANOSEC) >
		    zfetch_min_sec_reap)
			dmu_zfetch_stream_remove(zf, zs);
		else
			numstreams++;
	}

	/*
	 * The maximum number of streams is normally zfetch_max_streams,
	 * but for small files we lower it such that it's at least possible
	 * for all the streams to be non-overlapping.
	 *
	 * If we are already at the maximum number of streams for this file,
	 * even after removing old streams, then don't create this stream.
	 */
	uint32_t max_streams = MAX(1, MIN(zfetch_max_streams,
	    zf->zf_dnode->dn_maxblkid * zf->zf_dnode->dn_datablksz /
	    zfetch_max_distance));
	if (numstreams >= max_streams) {
		ZFETCHSTAT_BUMP(zfetchstat_max_streams);
		return;
	}

	zstream_t *zs = kmem_zalloc(sizeof (*zs), KM_SLEEP);
	zs->zs_blkid = blkid;
	zs->zs_pf_blkid = blkid;
	zs->zs_ipf_blkid = blkid;
	zs->zs_atime = gethrtime();
	mutex_init(&zs->zs_lock, NULL, MUTEX_DEFAULT, NULL);

	list_insert_head(&zf->zf_stream, zs);
}