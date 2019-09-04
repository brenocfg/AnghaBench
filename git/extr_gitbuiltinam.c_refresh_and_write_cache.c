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
 int /*<<< orphan*/  REFRESH_QUIET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_index ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refresh_and_write_cache(void)
{
	struct lock_file lock_file = LOCK_INIT;

	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
	refresh_cache(REFRESH_QUIET);
	if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die(_("unable to write index file"));
}