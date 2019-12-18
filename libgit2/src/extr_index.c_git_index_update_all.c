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
typedef  int /*<<< orphan*/  git_strarray ;
typedef  int /*<<< orphan*/  git_index_matched_path_cb ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_ACTION_UPDATE ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 int index_apply_to_wd_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int git_index_update_all(
	git_index *index,
	const git_strarray *pathspec,
	git_index_matched_path_cb cb,
	void *payload)
{
	int error = index_apply_to_wd_diff(index, INDEX_ACTION_UPDATE, pathspec, 0, cb, payload);
	if (error) /* make sure error is set if callback stopped iteration */
		git_error_set_after_callback(error);

	return error;
}