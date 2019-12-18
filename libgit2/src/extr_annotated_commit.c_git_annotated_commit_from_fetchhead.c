#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {void* remote_url; void* ref_name; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 scalar_t__ annotated_commit_init_from_id (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* git__strdup (char const*) ; 

int git_annotated_commit_from_fetchhead(
	git_annotated_commit **out,
	git_repository *repo,
	const char *branch_name,
	const char *remote_url,
	const git_oid *id)
{
	assert(repo && id && branch_name && remote_url);

	if (annotated_commit_init_from_id(out, repo, id, branch_name) < 0)
		return -1;

	(*out)->ref_name = git__strdup(branch_name);
	GIT_ERROR_CHECK_ALLOC((*out)->ref_name);

	(*out)->remote_url = git__strdup(remote_url);
	GIT_ERROR_CHECK_ALLOC((*out)->remote_url);

	return 0;
}