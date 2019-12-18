#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
struct TYPE_11__ {int /*<<< orphan*/  b_data; TYPE_3__* b_hdr; } ;
typedef  TYPE_2__ arc_buf_t ;
struct TYPE_10__ {int /*<<< orphan*/  b_freeze_lock; int /*<<< orphan*/ * b_freeze_cksum; } ;
struct TYPE_12__ {TYPE_1__ b_l1hdr; } ;
typedef  TYPE_3__ arc_buf_hdr_t ;

/* Variables and functions */
 scalar_t__ ARC_BUF_COMPRESSED (TYPE_2__*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int HDR_HAS_L1HDR (TYPE_3__*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int ZFS_DEBUG_MODIFY ; 
 int /*<<< orphan*/  arc_buf_size (TYPE_2__*) ; 
 int /*<<< orphan*/  arc_buf_watch (TYPE_2__*) ; 
 int arc_hdr_has_uncompressed_buf (TYPE_3__*) ; 
 int /*<<< orphan*/  fletcher_2_native (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int zfs_flags ; 

__attribute__((used)) static void
arc_cksum_compute(arc_buf_t *buf)
{
	arc_buf_hdr_t *hdr = buf->b_hdr;

	if (!(zfs_flags & ZFS_DEBUG_MODIFY))
		return;

	ASSERT(HDR_HAS_L1HDR(hdr));

	mutex_enter(&buf->b_hdr->b_l1hdr.b_freeze_lock);
	if (hdr->b_l1hdr.b_freeze_cksum != NULL) {
		ASSERT(arc_hdr_has_uncompressed_buf(hdr));
		mutex_exit(&hdr->b_l1hdr.b_freeze_lock);
		return;
	} else if (ARC_BUF_COMPRESSED(buf)) {
		mutex_exit(&hdr->b_l1hdr.b_freeze_lock);
		return;
	}

	ASSERT(!ARC_BUF_COMPRESSED(buf));
	hdr->b_l1hdr.b_freeze_cksum = kmem_alloc(sizeof (zio_cksum_t),
	    KM_SLEEP);
	fletcher_2_native(buf->b_data, arc_buf_size(buf), NULL,
	    hdr->b_l1hdr.b_freeze_cksum);
	mutex_exit(&hdr->b_l1hdr.b_freeze_lock);
#ifdef illumos
	arc_buf_watch(buf);
#endif
}