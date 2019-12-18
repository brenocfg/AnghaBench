#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ debugfs_dir; int /*<<< orphan*/  debugfs_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 scalar_t__ debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 TYPE_1__ iproc_priv ; 
 int /*<<< orphan*/  spu_debugfs_stats ; 

void spu_setup_debugfs(void)
{
	if (!debugfs_initialized())
		return;

	if (!iproc_priv.debugfs_dir)
		iproc_priv.debugfs_dir = debugfs_create_dir(KBUILD_MODNAME,
							    NULL);

	if (!iproc_priv.debugfs_stats)
		/* Create file with permissions S_IRUSR */
		debugfs_create_file("stats", 0400, iproc_priv.debugfs_dir,
				    &iproc_priv, &spu_debugfs_stats);
}