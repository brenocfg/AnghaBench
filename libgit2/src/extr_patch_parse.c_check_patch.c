#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hunks; TYPE_5__* delta; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
typedef  TYPE_4__ git_patch_parsed ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_10__ {scalar_t__ mode; scalar_t__ id_abbrev; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ id_abbrev; int /*<<< orphan*/  id; scalar_t__ path; } ;
struct TYPE_12__ {scalar_t__ status; int flags; TYPE_3__ new_file; TYPE_2__ old_file; } ;
typedef  TYPE_5__ git_diff_delta ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ GIT_DELTA_MODIFIED ; 
 int GIT_DIFF_FLAG_BINARY ; 
 scalar_t__ check_filenames (TYPE_4__*) ; 
 scalar_t__ git_array_size (int /*<<< orphan*/ ) ; 
 int git_parse_err (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int check_patch(git_patch_parsed *patch)
{
	git_diff_delta *delta = patch->base.delta;

	if (check_filenames(patch) < 0)
		return -1;

	if (delta->old_file.path &&
	    delta->status != GIT_DELTA_DELETED &&
	    !delta->new_file.mode)
		delta->new_file.mode = delta->old_file.mode;

	if (delta->status == GIT_DELTA_MODIFIED &&
	    !(delta->flags & GIT_DIFF_FLAG_BINARY) &&
	    delta->new_file.mode == delta->old_file.mode &&
	    git_array_size(patch->base.hunks) == 0)
		return git_parse_err("patch with no hunks");

	if (delta->status == GIT_DELTA_ADDED) {
		memset(&delta->old_file.id, 0x0, sizeof(git_oid));
		delta->old_file.id_abbrev = 0;
	}

	if (delta->status == GIT_DELTA_DELETED) {
		memset(&delta->new_file.id, 0x0, sizeof(git_oid));
		delta->new_file.id_abbrev = 0;
	}

	return 0;
}