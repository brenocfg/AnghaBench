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
typedef  int /*<<< orphan*/  kmutex_t ;
struct TYPE_11__ {TYPE_3__* b_hdr; } ;
typedef  TYPE_2__ arc_buf_t ;
struct TYPE_10__ {scalar_t__ b_state; int /*<<< orphan*/ * b_freeze_cksum; } ;
struct TYPE_12__ {TYPE_1__ b_l1hdr; } ;
typedef  TYPE_3__ arc_buf_hdr_t ;

/* Variables and functions */
 scalar_t__ ARC_BUF_COMPRESSED (TYPE_2__*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int HDR_HAS_L1HDR (TYPE_3__*) ; 
 int /*<<< orphan*/ * HDR_LOCK (TYPE_3__*) ; 
 int ZFS_DEBUG_MODIFY ; 
 scalar_t__ arc_anon ; 
 int /*<<< orphan*/  arc_cksum_compute (TYPE_2__*) ; 
 scalar_t__ arc_hdr_has_uncompressed_buf (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int zfs_flags ; 

void
arc_buf_freeze(arc_buf_t *buf)
{
	arc_buf_hdr_t *hdr = buf->b_hdr;
	kmutex_t *hash_lock;

	if (!(zfs_flags & ZFS_DEBUG_MODIFY))
		return;

	if (ARC_BUF_COMPRESSED(buf)) {
		ASSERT(hdr->b_l1hdr.b_freeze_cksum == NULL ||
		    arc_hdr_has_uncompressed_buf(hdr));
		return;
	}

	hash_lock = HDR_LOCK(hdr);
	mutex_enter(hash_lock);

	ASSERT(HDR_HAS_L1HDR(hdr));
	ASSERT(hdr->b_l1hdr.b_freeze_cksum != NULL ||
	    hdr->b_l1hdr.b_state == arc_anon);
	arc_cksum_compute(buf);
	mutex_exit(hash_lock);
}