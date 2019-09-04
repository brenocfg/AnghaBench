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
struct untracked_cache_dir {int dirs_nr; struct untracked_cache_dir** dirs; scalar_t__ untracked_nr; scalar_t__ valid; } ;

/* Variables and functions */

__attribute__((used)) static void do_invalidate_gitignore(struct untracked_cache_dir *dir)
{
	int i;
	dir->valid = 0;
	dir->untracked_nr = 0;
	for (i = 0; i < dir->dirs_nr; i++)
		do_invalidate_gitignore(dir->dirs[i]);
}