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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  ref_name; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int annotated_commit_init_from_id (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/  const*) ; 
 int git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int git_annotated_commit_from_ref(
	git_annotated_commit **out,
	git_repository *repo,
	const git_reference *ref)
{
	git_object *peeled;
	int error = 0;

	assert(out && repo && ref);

	*out = NULL;

	if ((error = git_reference_peel(&peeled, ref, GIT_OBJECT_COMMIT)) < 0)
		return error;

	error = annotated_commit_init_from_id(out,
		repo,
		git_object_id(peeled),
		git_reference_name(ref));

	if (!error) {
		(*out)->ref_name = git__strdup(git_reference_name(ref));
		GIT_ERROR_CHECK_ALLOC((*out)->ref_name);
	}

	git_object_free(peeled);
	return error;
}