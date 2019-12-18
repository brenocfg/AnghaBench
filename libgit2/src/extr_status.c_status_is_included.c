#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
struct TYPE_12__ {TYPE_2__ opts; } ;
typedef  TYPE_4__ git_status_list ;
struct TYPE_9__ {scalar_t__ mode; } ;
struct TYPE_11__ {scalar_t__ mode; } ;
struct TYPE_13__ {scalar_t__ status; TYPE_1__ new_file; TYPE_3__ old_file; } ;
typedef  TYPE_5__ git_diff_delta ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ GIT_FILEMODE_COMMIT ; 
 int GIT_STATUS_OPT_EXCLUDE_SUBMODULES ; 

__attribute__((used)) static bool status_is_included(
	git_status_list *status,
	git_diff_delta *head2idx,
	git_diff_delta *idx2wd)
{
	if (!(status->opts.flags & GIT_STATUS_OPT_EXCLUDE_SUBMODULES))
		return 1;

	/* if excluding submodules and this is a submodule everywhere */
	if (head2idx) {
		if (head2idx->status != GIT_DELTA_ADDED &&
			head2idx->old_file.mode != GIT_FILEMODE_COMMIT)
			return 1;
		if (head2idx->status != GIT_DELTA_DELETED &&
			head2idx->new_file.mode != GIT_FILEMODE_COMMIT)
			return 1;
	}
	if (idx2wd) {
		if (idx2wd->status != GIT_DELTA_ADDED &&
			idx2wd->old_file.mode != GIT_FILEMODE_COMMIT)
			return 1;
		if (idx2wd->status != GIT_DELTA_DELETED &&
			idx2wd->new_file.mode != GIT_FILEMODE_COMMIT)
			return 1;
	}

	/* only get here if every valid mode is GIT_FILEMODE_COMMIT */
	return 0;
}