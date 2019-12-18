#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ tag_state ;
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
#define  GIT_OBJECT_COMMIT 129 
#define  GIT_OBJECT_TAG 128 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  print_commit (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  print_name (char const*) ; 
 int /*<<< orphan*/  print_tag (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int each_tag(const char *name, tag_state *state)
{
	git_repository *repo = state->repo;
	git_object *obj;

	check_lg2(git_revparse_single(&obj, repo, name),
			"Failed to lookup rev", name);

	switch (git_object_type(obj)) {
		case GIT_OBJECT_TAG:
			print_tag((git_tag *) obj, state);
			break;
		case GIT_OBJECT_COMMIT:
			print_commit((git_commit *) obj, name, state);
			break;
		default:
			print_name(name);
	}

	git_object_free(obj);
	return 0;
}