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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int retrieve_tag_reference (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int git_tag_delete(git_repository *repo, const char *tag_name)
{
	git_reference *tag_ref;
	git_buf ref_name = GIT_BUF_INIT;
	int error;

	error = retrieve_tag_reference(&tag_ref, &ref_name, repo, tag_name);

	git_buf_dispose(&ref_name);

	if (error < 0)
		return error;

	error = git_reference_delete(tag_ref);

	git_reference_free(tag_ref);

	return error;
}