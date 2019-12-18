#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;
typedef  int /*<<< orphan*/  arc_buf_hdr_t ;
typedef  int /*<<< orphan*/  arc_buf_contents_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  HDR_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int /*<<< orphan*/  arc_buf_alloc_impl (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  arc_buf_thaw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arc_hdr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_guid (int /*<<< orphan*/ *) ; 

arc_buf_t *
arc_alloc_buf(spa_t *spa, void *tag, arc_buf_contents_t type, int32_t size)
{
	arc_buf_hdr_t *hdr = arc_hdr_alloc(spa_load_guid(spa), size, size,
	    ZIO_COMPRESS_OFF, type);
	ASSERT(!MUTEX_HELD(HDR_LOCK(hdr)));

	arc_buf_t *buf = NULL;
	VERIFY0(arc_buf_alloc_impl(hdr, tag, B_FALSE, B_FALSE, &buf));
	arc_buf_thaw(buf);

	return (buf);
}