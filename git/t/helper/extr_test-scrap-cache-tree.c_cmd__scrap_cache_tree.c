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
struct lock_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/ * active_cache_tree ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int /*<<< orphan*/  the_index ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 

int cmd__scrap_cache_tree(int ac, const char **av)
{
	struct lock_file index_lock = LOCK_INIT;

	setup_git_directory();
	hold_locked_index(&index_lock, LOCK_DIE_ON_ERROR);
	if (read_cache() < 0)
		die("unable to read index file");
	active_cache_tree = NULL;
	if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
		die("unable to write index file");
	return 0;
}