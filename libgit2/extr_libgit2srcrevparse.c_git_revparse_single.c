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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_revparse_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

int git_revparse_single(git_object **out, git_repository *repo, const char *spec)
{
	int error;
	git_object *obj = NULL;
	git_reference *ref = NULL;

	*out = NULL;

	if ((error = git_revparse_ext(&obj, &ref, repo, spec)) < 0)
		goto cleanup;

	git_reference_free(ref);

	*out = obj;

	return 0;

cleanup:
	git_object_free(obj);
	git_reference_free(ref);
	return error;
}