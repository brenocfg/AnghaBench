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
struct untracked_cache_dir {scalar_t__ untracked_nr; int /*<<< orphan*/ * untracked; int /*<<< orphan*/  untracked_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_untracked(struct untracked_cache_dir *dir, const char *name)
{
	if (!dir)
		return;
	ALLOC_GROW(dir->untracked, dir->untracked_nr + 1,
		   dir->untracked_alloc);
	dir->untracked[dir->untracked_nr++] = xstrdup(name);
}