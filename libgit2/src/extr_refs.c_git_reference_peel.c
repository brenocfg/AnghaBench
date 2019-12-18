#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  oid; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_1__ target; int /*<<< orphan*/  peel; } ;
typedef  TYPE_2__ git_reference ;
typedef  scalar_t__ git_object_t ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_TAG ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int git_object_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_owner (TYPE_2__ const*) ; 
 int git_reference_resolve (TYPE_2__**,TYPE_2__ const*) ; 
 int peel_error (int,TYPE_2__ const*,char*) ; 

int git_reference_peel(
	git_object **peeled,
	const git_reference *ref,
	git_object_t target_type)
{
	const git_reference *resolved = NULL;
	git_reference *allocated = NULL;
	git_object *target = NULL;
	int error;

	assert(ref);

	if (ref->type == GIT_REFERENCE_DIRECT) {
		resolved = ref;
	} else {
		if ((error = git_reference_resolve(&allocated, ref)) < 0)
			return peel_error(error, ref, "Cannot resolve reference");

		resolved = allocated;
	}

	/*
	 * If we try to peel an object to a tag, we cannot use
	 * the fully peeled object, as that will always resolve
	 * to a commit. So we only want to use the peeled value
	 * if it is not zero and the target is not a tag.
	 */
	if (target_type != GIT_OBJECT_TAG && !git_oid_is_zero(&resolved->peel)) {
		error = git_object_lookup(&target,
			git_reference_owner(ref), &resolved->peel, GIT_OBJECT_ANY);
	} else {
		error = git_object_lookup(&target,
			git_reference_owner(ref), &resolved->target.oid, GIT_OBJECT_ANY);
	}

	if (error < 0) {
		peel_error(error, ref, "Cannot retrieve reference target");
		goto cleanup;
	}

	if (target_type == GIT_OBJECT_ANY && git_object_type(target) != GIT_OBJECT_TAG)
		error = git_object_dup(peeled, target);
	else
		error = git_object_peel(peeled, target, target_type);

cleanup:
	git_object_free(target);
	git_reference_free(allocated);

	return error;
}