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
 int /*<<< orphan*/  GIT_UNUSED (size_t) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int revparse__ext (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,char const*) ; 

int git_revparse_ext(
	git_object **object_out,
	git_reference **reference_out,
	git_repository *repo,
	const char *spec)
{
	int error;
	size_t identifier_len;
	git_object *obj = NULL;
	git_reference *ref = NULL;

	if ((error = revparse__ext(&obj, &ref, &identifier_len, repo, spec)) < 0)
		goto cleanup;

	*object_out = obj;
	*reference_out = ref;
	GIT_UNUSED(identifier_len);

	return 0;

cleanup:
	git_object_free(obj);
	git_reference_free(ref);
	return error;
}