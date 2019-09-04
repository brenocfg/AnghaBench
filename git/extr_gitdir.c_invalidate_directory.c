#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct untracked_cache_dir {int dirs_nr; TYPE_1__** dirs; scalar_t__ untracked_nr; scalar_t__ valid; } ;
struct untracked_cache {int /*<<< orphan*/  dir_invalidated; } ;
struct TYPE_2__ {scalar_t__ recurse; } ;

/* Variables and functions */

__attribute__((used)) static void invalidate_directory(struct untracked_cache *uc,
				 struct untracked_cache_dir *dir)
{
	int i;

	/*
	 * Invalidation increment here is just roughly correct. If
	 * untracked_nr or any of dirs[].recurse is non-zero, we
	 * should increment dir_invalidated too. But that's more
	 * expensive to do.
	 */
	if (dir->valid)
		uc->dir_invalidated++;

	dir->valid = 0;
	dir->untracked_nr = 0;
	for (i = 0; i < dir->dirs_nr; i++)
		dir->dirs[i]->recurse = 0;
}