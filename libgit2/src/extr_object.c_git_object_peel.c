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
typedef  scalar_t__ git_object_t ;
typedef  int /*<<< orphan*/  const git_object ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_BLOB ; 
 scalar_t__ GIT_OBJECT_COMMIT ; 
 scalar_t__ GIT_OBJECT_TAG ; 
 scalar_t__ GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  assert (int) ; 
 int check_type_combination (scalar_t__,scalar_t__) ; 
 int dereference_object (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int git_object_dup (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/  const*) ; 
 int peel_error (int,int /*<<< orphan*/ ,scalar_t__) ; 

int git_object_peel(
	git_object **peeled,
	const git_object *object,
	git_object_t target_type)
{
	git_object *source, *deref = NULL;
	int error;

	assert(object && peeled);

	assert(target_type == GIT_OBJECT_TAG ||
		target_type == GIT_OBJECT_COMMIT ||
		target_type == GIT_OBJECT_TREE ||
		target_type == GIT_OBJECT_BLOB ||
		target_type == GIT_OBJECT_ANY);

	if ((error = check_type_combination(git_object_type(object), target_type)) < 0)
		return peel_error(error, git_object_id(object), target_type);

	if (git_object_type(object) == target_type)
		return git_object_dup(peeled, (git_object *)object);

	source = (git_object *)object;

	while (!(error = dereference_object(&deref, source))) {

		if (source != object)
			git_object_free(source);

		if (git_object_type(deref) == target_type) {
			*peeled = deref;
			return 0;
		}

		if (target_type == GIT_OBJECT_ANY &&
			git_object_type(deref) != git_object_type(object))
		{
			*peeled = deref;
			return 0;
		}

		source = deref;
		deref = NULL;
	}

	if (source != object)
		git_object_free(source);

	git_object_free(deref);

	if (error)
		error = peel_error(error, git_object_id(object), target_type);

	return error;
}