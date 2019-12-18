#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int git_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int status; TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 134 
#define  GIT_DELTA_CONFLICTED 133 
#define  GIT_DELTA_COPIED 132 
#define  GIT_DELTA_DELETED 131 
#define  GIT_DELTA_MODIFIED 130 
#define  GIT_DELTA_RENAMED 129 
#define  GIT_DELTA_TYPECHANGE 128 
 unsigned int GIT_STATUS_CONFLICTED ; 
 unsigned int GIT_STATUS_CURRENT ; 
 unsigned int GIT_STATUS_INDEX_DELETED ; 
 unsigned int GIT_STATUS_INDEX_MODIFIED ; 
 unsigned int GIT_STATUS_INDEX_NEW ; 
 unsigned int GIT_STATUS_INDEX_RENAMED ; 
 unsigned int GIT_STATUS_INDEX_TYPECHANGE ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int index_delta2status(const git_diff_delta *head2idx)
{
	git_status_t st = GIT_STATUS_CURRENT;

	switch (head2idx->status) {
	case GIT_DELTA_ADDED:
	case GIT_DELTA_COPIED:
		st = GIT_STATUS_INDEX_NEW;
		break;
	case GIT_DELTA_DELETED:
		st = GIT_STATUS_INDEX_DELETED;
		break;
	case GIT_DELTA_MODIFIED:
		st = GIT_STATUS_INDEX_MODIFIED;
		break;
	case GIT_DELTA_RENAMED:
		st = GIT_STATUS_INDEX_RENAMED;

		if (!git_oid_equal(&head2idx->old_file.id, &head2idx->new_file.id))
			st |= GIT_STATUS_INDEX_MODIFIED;
		break;
	case GIT_DELTA_TYPECHANGE:
		st = GIT_STATUS_INDEX_TYPECHANGE;
		break;
	case GIT_DELTA_CONFLICTED:
		st = GIT_STATUS_CONFLICTED;
		break;
	default:
		break;
	}

	return st;
}