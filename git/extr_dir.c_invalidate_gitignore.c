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
struct untracked_cache_dir {int dummy; } ;
struct untracked_cache {int /*<<< orphan*/  gitignore_invalidated; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_invalidate_gitignore (struct untracked_cache_dir*) ; 

__attribute__((used)) static void invalidate_gitignore(struct untracked_cache *uc,
				 struct untracked_cache_dir *dir)
{
	uc->gitignore_invalidated++;
	do_invalidate_gitignore(dir);
}