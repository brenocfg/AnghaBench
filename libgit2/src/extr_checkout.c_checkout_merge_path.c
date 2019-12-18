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
struct TYPE_11__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_merge_file_result ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_9__ {char* our_label; char* their_label; } ;
struct TYPE_12__ {TYPE_1__ opts; int /*<<< orphan*/  repo; } ;
typedef  TYPE_4__ checkout_data ;
struct TYPE_13__ {TYPE_2__* ours; int /*<<< orphan*/  name_collision; } ;
typedef  TYPE_5__ checkout_conflictdata ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int checkout_path_suffixed (int /*<<< orphan*/ *,char const*) ; 
 int git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_merge_path(
	git_buf *out,
	checkout_data *data,
	checkout_conflictdata *conflict,
	git_merge_file_result *result)
{
	const char *our_label_raw, *their_label_raw, *suffix;
	int error = 0;

	if ((error = git_buf_joinpath(out, git_repository_workdir(data->repo), result->path)) < 0)
		return error;

	/* Most conflicts simply use the filename in the index */
	if (!conflict->name_collision)
		return 0;

	/* Rename 2->1 conflicts need the branch name appended */
	our_label_raw = data->opts.our_label ? data->opts.our_label : "ours";
	their_label_raw = data->opts.their_label ? data->opts.their_label : "theirs";
	suffix = strcmp(result->path, conflict->ours->path) == 0 ? our_label_raw : their_label_raw;

	if ((error = checkout_path_suffixed(out, suffix)) < 0)
		return error;

	return 0;
}