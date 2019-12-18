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
 struct lock_file LOCK_INIT ; 
 int REFRESH_QUIET ; 
 int REFRESH_UNMERGED ; 
 int /*<<< orphan*/  discard_cache () ; 
 int hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  refresh_cache (int) ; 
 int /*<<< orphan*/  repo_update_index_if_able (int /*<<< orphan*/ ,struct lock_file*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void refresh_index_quietly(void)
{
	struct lock_file lock_file = LOCK_INIT;
	int fd;

	fd = hold_locked_index(&lock_file, 0);
	if (fd < 0)
		return;
	discard_cache();
	read_cache();
	refresh_cache(REFRESH_QUIET|REFRESH_UNMERGED);
	repo_update_index_if_able(the_repository, &lock_file);
}