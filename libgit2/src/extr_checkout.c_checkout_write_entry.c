#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_15__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_14__ {char* our_label; char* their_label; } ;
struct TYPE_17__ {int strategy; TYPE_1__ opts; } ;
typedef  TYPE_4__ checkout_data ;
struct TYPE_18__ {TYPE_2__ const* ours; scalar_t__ directoryfile; scalar_t__ name_collision; TYPE_2__ const* theirs; } ;
typedef  TYPE_5__ checkout_conflictdata ;

/* Variables and functions */
 int GIT_CHECKOUT_UPDATE_ONLY ; 
 int GIT_CHECKOUT_USE_OURS ; 
 int GIT_CHECKOUT_USE_THEIRS ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ checkout_path_suffixed (TYPE_3__*,char const*) ; 
 int checkout_safe_for_update_only (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ checkout_target_fullpath (TYPE_3__**,TYPE_4__*,char*) ; 
 int checkout_write_content (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int checkout_write_entry(
	checkout_data *data,
	checkout_conflictdata *conflict,
	const git_index_entry *side)
{
	const char *hint_path = NULL, *suffix;
	git_buf *fullpath;
	struct stat st;
	int error;

	assert (side == conflict->ours || side == conflict->theirs);

	if (checkout_target_fullpath(&fullpath, data, side->path) < 0)
		return -1;

	if ((conflict->name_collision || conflict->directoryfile) &&
		(data->strategy & GIT_CHECKOUT_USE_OURS) == 0 &&
		(data->strategy & GIT_CHECKOUT_USE_THEIRS) == 0) {

		if (side == conflict->ours)
			suffix = data->opts.our_label ? data->opts.our_label :
				"ours";
		else
			suffix = data->opts.their_label ? data->opts.their_label :
				"theirs";

		if (checkout_path_suffixed(fullpath, suffix) < 0)
			return -1;

		hint_path = side->path;
	}

	if ((data->strategy & GIT_CHECKOUT_UPDATE_ONLY) != 0 &&
		(error = checkout_safe_for_update_only(data, fullpath->ptr, side->mode)) <= 0)
		return error;

	if (!S_ISGITLINK(side->mode))
		return checkout_write_content(data,
					      &side->id, fullpath->ptr, hint_path, side->mode, &st);

	return 0;
}