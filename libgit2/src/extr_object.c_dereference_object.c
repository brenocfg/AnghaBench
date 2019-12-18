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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_tag ;
typedef  int git_object_t ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int GIT_EPEEL ; 
#define  GIT_OBJECT_BLOB 131 
#define  GIT_OBJECT_COMMIT 130 
#define  GIT_OBJECT_TAG 129 
#define  GIT_OBJECT_TREE 128 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_object_type (int /*<<< orphan*/ *) ; 
 int git_tag_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dereference_object(git_object **dereferenced, git_object *obj)
{
	git_object_t type = git_object_type(obj);

	switch (type) {
	case GIT_OBJECT_COMMIT:
		return git_commit_tree((git_tree **)dereferenced, (git_commit*)obj);

	case GIT_OBJECT_TAG:
		return git_tag_target(dereferenced, (git_tag*)obj);

	case GIT_OBJECT_BLOB:
	case GIT_OBJECT_TREE:
		return GIT_EPEEL;

	default:
		return GIT_EINVALIDSPEC;
	}
}