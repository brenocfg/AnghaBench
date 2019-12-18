#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_merge_options ;
typedef  int /*<<< orphan*/  git_merge_file_options ;
typedef  int /*<<< orphan*/  git_merge_diff_list ;
typedef  int /*<<< orphan*/  git_merge_diff ;

/* Variables and functions */
 int merge_conflict_resolve_contents (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int merge_conflict_resolve_one_removed (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int merge_conflict_resolve_one_renamed (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int merge_conflict_resolve_trivial (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int merge_conflict_resolve(
	int *out,
	git_merge_diff_list *diff_list,
	const git_merge_diff *conflict,
	const git_merge_options *merge_opts,
	const git_merge_file_options *file_opts)
{
	int resolved = 0;
	int error = 0;

	*out = 0;

	if ((error = merge_conflict_resolve_trivial(
			&resolved, diff_list, conflict)) < 0)
		goto done;

	if (!resolved && (error = merge_conflict_resolve_one_removed(
			&resolved, diff_list, conflict)) < 0)
		goto done;

	if (!resolved && (error = merge_conflict_resolve_one_renamed(
			&resolved, diff_list, conflict)) < 0)
		goto done;

	if (!resolved && (error = merge_conflict_resolve_contents(
			&resolved, diff_list, conflict, merge_opts, file_opts)) < 0)
		goto done;

	*out = resolved;

done:
	return error;
}