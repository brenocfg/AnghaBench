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

/* Variables and functions */
 int /*<<< orphan*/  abd_init () ; 
 int /*<<< orphan*/  arc_init () ; 
 int /*<<< orphan*/  dbuf_init () ; 
 int /*<<< orphan*/  dmu_objset_init () ; 
 int /*<<< orphan*/  dnode_init () ; 
 int /*<<< orphan*/  l2arc_init () ; 
 int /*<<< orphan*/  sa_cache_init () ; 
 int /*<<< orphan*/  xuio_stat_init () ; 
 int /*<<< orphan*/  zfetch_init () ; 
 int /*<<< orphan*/  zfs_dbgmsg_init () ; 
 int /*<<< orphan*/  zio_compress_init () ; 

void
dmu_init(void)
{
	abd_init();
	zfs_dbgmsg_init();
	sa_cache_init();
	xuio_stat_init();
	dmu_objset_init();
	dnode_init();
	zfetch_init();
	zio_compress_init();
	l2arc_init();
	arc_init();
	dbuf_init();
}