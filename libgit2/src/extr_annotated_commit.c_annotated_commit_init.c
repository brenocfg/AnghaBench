#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_6__ {char* id_str; struct TYPE_6__* description; int /*<<< orphan*/  commit; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ANNOTATED_COMMIT_REAL ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 size_t GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 
 TYPE_1__* git__strdup (char const*) ; 
 int git_commit_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int annotated_commit_init(
	git_annotated_commit **out,
	git_commit *commit,
	const char *description)
{
	git_annotated_commit *annotated_commit;
	int error = 0;

	assert(out && commit);

	*out = NULL;

	annotated_commit = git__calloc(1, sizeof(git_annotated_commit));
	GIT_ERROR_CHECK_ALLOC(annotated_commit);

	annotated_commit->type = GIT_ANNOTATED_COMMIT_REAL;

	if ((error = git_commit_dup(&annotated_commit->commit, commit)) < 0)
		goto done;

	git_oid_fmt(annotated_commit->id_str, git_commit_id(commit));
	annotated_commit->id_str[GIT_OID_HEXSZ] = '\0';

	if (!description)
		description = annotated_commit->id_str;

	annotated_commit->description = git__strdup(description);
	GIT_ERROR_CHECK_ALLOC(annotated_commit->description);

done:
	if (!error)
		*out = annotated_commit;

	return error;
}