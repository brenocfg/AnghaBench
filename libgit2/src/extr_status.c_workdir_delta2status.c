#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int git_status_t ;
struct TYPE_9__ {int /*<<< orphan*/  id; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct TYPE_10__ {int status; TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
struct TYPE_11__ {int /*<<< orphan*/  new_src; int /*<<< orphan*/  old_src; } ;
typedef  TYPE_4__ git_diff ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 137 
#define  GIT_DELTA_CONFLICTED 136 
#define  GIT_DELTA_COPIED 135 
#define  GIT_DELTA_DELETED 134 
#define  GIT_DELTA_IGNORED 133 
#define  GIT_DELTA_MODIFIED 132 
#define  GIT_DELTA_RENAMED 131 
#define  GIT_DELTA_TYPECHANGE 130 
#define  GIT_DELTA_UNREADABLE 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  GIT_DIFF_FLAG_VALID_ID ; 
 int /*<<< orphan*/  GIT_ITERATOR_TYPE_WORKDIR ; 
 unsigned int GIT_STATUS_CONFLICTED ; 
 unsigned int GIT_STATUS_CURRENT ; 
 unsigned int GIT_STATUS_IGNORED ; 
 unsigned int GIT_STATUS_WT_DELETED ; 
 unsigned int GIT_STATUS_WT_MODIFIED ; 
 unsigned int GIT_STATUS_WT_NEW ; 
 unsigned int GIT_STATUS_WT_RENAMED ; 
 unsigned int GIT_STATUS_WT_TYPECHANGE ; 
 unsigned int GIT_STATUS_WT_UNREADABLE ; 
 int /*<<< orphan*/  git_diff__oid_for_file (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_is_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int workdir_delta2status(
	git_diff *diff, git_diff_delta *idx2wd)
{
	git_status_t st = GIT_STATUS_CURRENT;

	switch (idx2wd->status) {
	case GIT_DELTA_ADDED:
	case GIT_DELTA_COPIED:
	case GIT_DELTA_UNTRACKED:
		st = GIT_STATUS_WT_NEW;
		break;
	case GIT_DELTA_UNREADABLE:
		st = GIT_STATUS_WT_UNREADABLE;
		break;
	case GIT_DELTA_DELETED:
		st = GIT_STATUS_WT_DELETED;
		break;
	case GIT_DELTA_MODIFIED:
		st = GIT_STATUS_WT_MODIFIED;
		break;
	case GIT_DELTA_IGNORED:
		st = GIT_STATUS_IGNORED;
		break;
	case GIT_DELTA_RENAMED:
		st = GIT_STATUS_WT_RENAMED;

		if (!git_oid_equal(&idx2wd->old_file.id, &idx2wd->new_file.id)) {
			/* if OIDs don't match, we might need to calculate them now to
			 * discern between RENAMED vs RENAMED+MODIFED
			 */
			if (git_oid_is_zero(&idx2wd->old_file.id) &&
				diff->old_src == GIT_ITERATOR_TYPE_WORKDIR &&
				!git_diff__oid_for_file(
					&idx2wd->old_file.id, diff, idx2wd->old_file.path,
					idx2wd->old_file.mode, idx2wd->old_file.size))
			idx2wd->old_file.flags |= GIT_DIFF_FLAG_VALID_ID;

			if (git_oid_is_zero(&idx2wd->new_file.id) &&
				diff->new_src == GIT_ITERATOR_TYPE_WORKDIR &&
				!git_diff__oid_for_file(
					&idx2wd->new_file.id, diff, idx2wd->new_file.path,
					idx2wd->new_file.mode, idx2wd->new_file.size))
				idx2wd->new_file.flags |= GIT_DIFF_FLAG_VALID_ID;

			if (!git_oid_equal(&idx2wd->old_file.id, &idx2wd->new_file.id))
				st |= GIT_STATUS_WT_MODIFIED;
		}
		break;
	case GIT_DELTA_TYPECHANGE:
		st = GIT_STATUS_WT_TYPECHANGE;
		break;
	case GIT_DELTA_CONFLICTED:
		st = GIT_STATUS_CONFLICTED;
		break;
	default:
		break;
	}

	return st;
}