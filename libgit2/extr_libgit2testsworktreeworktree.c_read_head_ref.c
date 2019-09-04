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
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference__read_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_head_ref(git_repository *repo, const char *path, void *payload)
{
	git_vector *refs = (git_vector *) payload;
	git_reference *head;

	GIT_UNUSED(repo);

	cl_git_pass(git_reference__read_head(&head, repo, path));

	git_vector_insert(refs, head);

	return 0;
}