#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  id; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_4__ git_index_entry ;
struct TYPE_11__ {int /*<<< orphan*/  (* strcomp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  deltas; } ;
struct TYPE_15__ {TYPE_1__ base; } ;
typedef  TYPE_5__ git_diff_generated ;
struct TYPE_13__ {int /*<<< orphan*/  id; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int status; TYPE_3__ new_file; TYPE_2__ old_file; } ;
typedef  TYPE_6__ git_diff_delta ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 133 
#define  GIT_DELTA_DELETED 132 
#define  GIT_DELTA_MODIFIED 131 
#define  GIT_DELTA_UNMODIFIED 130 
#define  GIT_DELTA_UNREADABLE 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  git_oid__cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* git_vector_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static git_diff_delta *diff_delta__last_for_item(
	git_diff_generated *diff,
	const git_index_entry *item)
{
	git_diff_delta *delta = git_vector_last(&diff->base.deltas);
	if (!delta)
		return NULL;

	switch (delta->status) {
	case GIT_DELTA_UNMODIFIED:
	case GIT_DELTA_DELETED:
		if (git_oid__cmp(&delta->old_file.id, &item->id) == 0)
			return delta;
		break;
	case GIT_DELTA_ADDED:
		if (git_oid__cmp(&delta->new_file.id, &item->id) == 0)
			return delta;
		break;
	case GIT_DELTA_UNREADABLE:
	case GIT_DELTA_UNTRACKED:
		if (diff->base.strcomp(delta->new_file.path, item->path) == 0 &&
			git_oid__cmp(&delta->new_file.id, &item->id) == 0)
			return delta;
		break;
	case GIT_DELTA_MODIFIED:
		if (git_oid__cmp(&delta->old_file.id, &item->id) == 0 ||
		    (delta->new_file.mode == item->mode &&
			git_oid__cmp(&delta->new_file.id, &item->id) == 0))
			return delta;
		break;
	default:
		break;
	}

	return NULL;
}