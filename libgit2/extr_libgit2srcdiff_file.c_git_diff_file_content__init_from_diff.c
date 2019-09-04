#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  flags; TYPE_1__* file; int /*<<< orphan*/  repo; int /*<<< orphan*/  driver; int /*<<< orphan*/  src; } ;
typedef  TYPE_2__ git_diff_file_content ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
struct TYPE_14__ {int status; TYPE_1__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
struct TYPE_11__ {int flags; } ;
struct TYPE_15__ {TYPE_10__ opts; int /*<<< orphan*/  attrsession; int /*<<< orphan*/  new_src; int /*<<< orphan*/  old_src; int /*<<< orphan*/  repo; } ;
typedef  TYPE_4__ git_diff ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 134 
#define  GIT_DELTA_COPIED 133 
#define  GIT_DELTA_DELETED 132 
#define  GIT_DELTA_MODIFIED 131 
#define  GIT_DELTA_RENAMED 130 
#define  GIT_DELTA_UNREADABLE 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  GIT_DIFF_FLAG__NO_DATA ; 
 int GIT_DIFF_SHOW_UNTRACKED_CONTENT ; 
 int diff_file_content_init_common (TYPE_2__*,TYPE_10__*) ; 
 scalar_t__ git_diff_driver_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int git_diff_file_content__init_from_diff(
	git_diff_file_content *fc,
	git_diff *diff,
	git_diff_delta *delta,
	bool use_old)
{
	bool has_data = true;

	memset(fc, 0, sizeof(*fc));
	fc->repo = diff->repo;
	fc->file = use_old ? &delta->old_file : &delta->new_file;
	fc->src  = use_old ? diff->old_src : diff->new_src;

	if (git_diff_driver_lookup(&fc->driver, fc->repo,
		    &diff->attrsession, fc->file->path) < 0)
		return -1;

	switch (delta->status) {
	case GIT_DELTA_ADDED:
		has_data = !use_old; break;
	case GIT_DELTA_DELETED:
		has_data = use_old; break;
	case GIT_DELTA_UNTRACKED:
		has_data = !use_old &&
			(diff->opts.flags & GIT_DIFF_SHOW_UNTRACKED_CONTENT) != 0;
		break;
	case GIT_DELTA_UNREADABLE:
	case GIT_DELTA_MODIFIED:
	case GIT_DELTA_COPIED:
	case GIT_DELTA_RENAMED:
		break;
	default:
		has_data = false;
		break;
	}

	if (!has_data)
		fc->flags |= GIT_DIFF_FLAG__NO_DATA;

	return diff_file_content_init_common(fc, &diff->opts);
}