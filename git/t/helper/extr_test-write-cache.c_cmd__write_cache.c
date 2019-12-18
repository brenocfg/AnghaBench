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
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_index ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 

int cmd__write_cache(int argc, const char **argv)
{
	struct lock_file index_lock = LOCK_INIT;
	int i, cnt = 1;
	if (argc == 2)
		cnt = strtol(argv[1], NULL, 0);
	setup_git_directory();
	read_cache();
	for (i = 0; i < cnt; i++) {
		hold_locked_index(&index_lock, LOCK_DIE_ON_ERROR);
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
			die("unable to write index file");
	}

	return 0;
}