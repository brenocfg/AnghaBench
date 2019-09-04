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
typedef  int /*<<< orphan*/  git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 char* git_reference_name (int /*<<< orphan*/ *) ; 
 int git_reference_resolve (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int ref_to_update (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int remote_head_for_fetchspec_src (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remote_head_for_ref(git_remote_head **out, git_remote *remote, git_refspec *spec, git_vector *update_heads, git_reference *ref)
{
	git_reference *resolved_ref = NULL;
	git_buf remote_name = GIT_BUF_INIT;
	git_config *config = NULL;
	const char *ref_name;
	int error = 0, update;

	assert(out && spec && ref);

	*out = NULL;

	error = git_reference_resolve(&resolved_ref, ref);

	/* If we're in an unborn branch, let's pretend nothing happened */
	if (error == GIT_ENOTFOUND && git_reference_type(ref) == GIT_REFERENCE_SYMBOLIC) {
		ref_name = git_reference_symbolic_target(ref);
		error = 0;
	} else {
		ref_name = git_reference_name(resolved_ref);
	}

	if ((error = ref_to_update(&update, &remote_name, remote, spec, ref_name)) < 0)
		goto cleanup;

	if (update)
		error = remote_head_for_fetchspec_src(out, update_heads, git_buf_cstr(&remote_name));

cleanup:
	git_buf_dispose(&remote_name);
	git_reference_free(resolved_ref);
	git_config_free(config);
	return error;
}