#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_dir_name (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ has_file_name (int /*<<< orphan*/ *,TYPE_1__*,size_t,int) ; 

__attribute__((used)) static int check_file_directory_collision(git_index *index,
		git_index_entry *entry, size_t pos, int ok_to_replace)
{
	if (has_file_name(index, entry, pos, ok_to_replace) < 0 ||
	    has_dir_name(index, entry, ok_to_replace) < 0) {
		git_error_set(GIT_ERROR_INDEX,
			"'%s' appears as both a file and a directory", entry->path);
		return -1;
	}

	return 0;
}