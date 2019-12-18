#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  l2ad_alloc; int /*<<< orphan*/  l2ad_vdev; int /*<<< orphan*/  l2ad_buflist; int /*<<< orphan*/  l2ad_mtx; } ;
typedef  TYPE_1__ l2arc_dev_t ;
struct TYPE_12__ {TYPE_1__* b_dev; } ;
typedef  TYPE_2__ l2arc_buf_hdr_t ;
struct TYPE_13__ {TYPE_2__ b_l2hdr; } ;
typedef  TYPE_3__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCSTAT_INCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARC_FLAG_HAS_L2HDR ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDR_GET_LSIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  HDR_HAS_L2HDR (TYPE_3__*) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_hdr_clear_flags (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_hdr_size (TYPE_3__*) ; 
 int /*<<< orphan*/  arcstat_l2_lsize ; 
 int /*<<< orphan*/  arcstat_l2_psize ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_space_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_remove_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
arc_hdr_l2hdr_destroy(arc_buf_hdr_t *hdr)
{
	l2arc_buf_hdr_t *l2hdr = &hdr->b_l2hdr;
	l2arc_dev_t *dev = l2hdr->b_dev;
	uint64_t psize = arc_hdr_size(hdr);

	ASSERT(MUTEX_HELD(&dev->l2ad_mtx));
	ASSERT(HDR_HAS_L2HDR(hdr));

	list_remove(&dev->l2ad_buflist, hdr);

	ARCSTAT_INCR(arcstat_l2_psize, -psize);
	ARCSTAT_INCR(arcstat_l2_lsize, -HDR_GET_LSIZE(hdr));

	vdev_space_update(dev->l2ad_vdev, -psize, 0, 0);

	(void) zfs_refcount_remove_many(&dev->l2ad_alloc, psize, hdr);
	arc_hdr_clear_flags(hdr, ARC_FLAG_HAS_L2HDR);
}