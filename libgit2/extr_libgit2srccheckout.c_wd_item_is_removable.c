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
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  DOT_GIT ; 
 scalar_t__ GIT_FILEMODE_TREE ; 
 scalar_t__ checkout_target_fullpath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wd_item_is_removable(
	checkout_data *data, const git_index_entry *wd)
{
	git_buf *full;

	if (wd->mode != GIT_FILEMODE_TREE)
		return true;

	if (checkout_target_fullpath(&full, data, wd->path) < 0)
		return false;

	return !full || !git_path_contains(full, DOT_GIT);
}