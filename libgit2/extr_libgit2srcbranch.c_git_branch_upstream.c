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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int git_branch_upstream_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_owner (int /*<<< orphan*/  const*) ; 

int git_branch_upstream(
	git_reference **tracking_out,
	const git_reference *branch)
{
	int error;
	git_buf tracking_name = GIT_BUF_INIT;

	if ((error = git_branch_upstream_name(&tracking_name,
		git_reference_owner(branch), git_reference_name(branch))) < 0)
			return error;

	error = git_reference_lookup(
		tracking_out,
		git_reference_owner(branch),
		git_buf_cstr(&tracking_name));

	git_buf_dispose(&tracking_name);
	return error;
}