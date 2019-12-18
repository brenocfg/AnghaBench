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
 int /*<<< orphan*/  abd_fini () ; 
 int /*<<< orphan*/  arc_fini () ; 
 int /*<<< orphan*/  dbuf_fini () ; 
 int /*<<< orphan*/  dmu_objset_fini () ; 
 int /*<<< orphan*/  dnode_fini () ; 
 int /*<<< orphan*/  l2arc_fini () ; 
 int /*<<< orphan*/  sa_cache_fini () ; 
 int /*<<< orphan*/  xuio_stat_fini () ; 
 int /*<<< orphan*/  zfetch_fini () ; 
 int /*<<< orphan*/  zfs_dbgmsg_fini () ; 
 int /*<<< orphan*/  zio_compress_fini () ; 

void
dmu_fini(void)
{
	arc_fini(); /* arc depends on l2arc, so arc must go first */
	l2arc_fini();
	zfetch_fini();
	zio_compress_fini();
	dbuf_fini();
	dnode_fini();
	dmu_objset_fini();
	xuio_stat_fini();
	sa_cache_fini();
	zfs_dbgmsg_fini();
	abd_fini();
}