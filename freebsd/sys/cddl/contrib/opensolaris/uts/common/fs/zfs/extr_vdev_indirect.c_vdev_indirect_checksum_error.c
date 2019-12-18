#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int io_flags; int /*<<< orphan*/  io_spa; } ;
typedef  TYPE_3__ zio_t ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ zio_bad_cksum_t ;
struct TYPE_14__ {int /*<<< orphan*/  vs_checksum_errors; } ;
struct TYPE_18__ {int /*<<< orphan*/  vdev_stat_lock; TYPE_1__ vdev_stat; } ;
typedef  TYPE_5__ vdev_t ;
struct TYPE_19__ {int /*<<< orphan*/  is_size; int /*<<< orphan*/  is_target_offset; TYPE_2__* is_good_child; } ;
typedef  TYPE_6__ indirect_split_t ;
struct TYPE_20__ {int /*<<< orphan*/ * ic_data; TYPE_5__* ic_vdev; } ;
typedef  TYPE_7__ indirect_child_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_15__ {int /*<<< orphan*/ * ic_data; } ;

/* Variables and functions */
 int ZIO_FLAG_SPECULATIVE ; 
 void* abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_ereport_post_checksum (int /*<<< orphan*/ ,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,TYPE_4__*) ; 

__attribute__((used)) static void
vdev_indirect_checksum_error(zio_t *zio,
    indirect_split_t *is, indirect_child_t *ic)
{
	vdev_t *vd = ic->ic_vdev;

	if (zio->io_flags & ZIO_FLAG_SPECULATIVE)
		return;

	mutex_enter(&vd->vdev_stat_lock);
	vd->vdev_stat.vs_checksum_errors++;
	mutex_exit(&vd->vdev_stat_lock);

	zio_bad_cksum_t zbc = { 0 };
	void *bad_buf = abd_borrow_buf_copy(ic->ic_data, is->is_size);
	abd_t *good_abd = is->is_good_child->ic_data;
	void *good_buf = abd_borrow_buf_copy(good_abd, is->is_size);
	zfs_ereport_post_checksum(zio->io_spa, vd, zio,
	    is->is_target_offset, is->is_size, good_buf, bad_buf, &zbc);
	abd_return_buf(ic->ic_data, bad_buf, is->is_size);
	abd_return_buf(good_abd, good_buf, is->is_size);
}