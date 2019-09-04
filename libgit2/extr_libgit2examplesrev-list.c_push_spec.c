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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int push_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int push_spec(git_repository *repo, git_revwalk *walk, const char *spec, int hide)
{
	int error;
	git_object *obj;

	if ((error = git_revparse_single(&obj, repo, spec)) < 0)
		return error;

	error = push_commit(walk, git_object_id(obj), hide);
	git_object_free(obj);
	return error;
}