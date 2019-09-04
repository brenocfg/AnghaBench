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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  any_left_hand_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ensure_base_rev_is_not_known_yet (int /*<<< orphan*/ *) ; 
 int ensure_base_rev_loaded (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,size_t,int /*<<< orphan*/ *,int) ; 
 int ensure_left_hand_identifier_is_not_known_yet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int extract_curly_braces_content (int /*<<< orphan*/ *,char const*,size_t*) ; 
 int extract_how_many (int*,char const*,size_t*) ; 
 int extract_path (int /*<<< orphan*/ *,char const*,size_t*) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int handle_at_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,size_t,int /*<<< orphan*/ *,char*) ; 
 int handle_caret_curly_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int handle_caret_parent_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int handle_colon_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int handle_grep_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int handle_linear_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

int revparse__ext(
	git_object **object_out,
	git_reference **reference_out,
	size_t *identifier_len_out,
	git_repository *repo,
	const char *spec)
{
	size_t pos = 0, identifier_len = 0;
	int error = -1, n;
	git_buf buf = GIT_BUF_INIT;

	git_reference *reference = NULL;
	git_object *base_rev = NULL;

	bool should_return_reference = true;

	assert(object_out && reference_out && repo && spec);

	*object_out = NULL;
	*reference_out = NULL;

	while (spec[pos]) {
		switch (spec[pos]) {
		case '^':
			should_return_reference = false;

			if ((error = ensure_base_rev_loaded(&base_rev, &reference, spec, identifier_len, repo, false)) < 0)
				goto cleanup;

			if (spec[pos+1] == '{') {
				git_object *temp_object = NULL;

				if ((error = extract_curly_braces_content(&buf, spec, &pos)) < 0)
					goto cleanup;

				if ((error = handle_caret_curly_syntax(&temp_object, base_rev, git_buf_cstr(&buf))) < 0)
					goto cleanup;

				git_object_free(base_rev);
				base_rev = temp_object;
			} else {
				git_object *temp_object = NULL;

				if ((error = extract_how_many(&n, spec, &pos)) < 0)
					goto cleanup;

				if ((error = handle_caret_parent_syntax(&temp_object, base_rev, n)) < 0)
					goto cleanup;

				git_object_free(base_rev);
				base_rev = temp_object;
			}
			break;

		case '~':
		{
			git_object *temp_object = NULL;

			should_return_reference = false;

			if ((error = extract_how_many(&n, spec, &pos)) < 0)
				goto cleanup;

			if ((error = ensure_base_rev_loaded(&base_rev, &reference, spec, identifier_len, repo, false)) < 0)
				goto cleanup;

			if ((error = handle_linear_syntax(&temp_object, base_rev, n)) < 0)
				goto cleanup;

			git_object_free(base_rev);
			base_rev = temp_object;
			break;
		}

		case ':':
		{
			git_object *temp_object = NULL;

			should_return_reference = false;

			if ((error = extract_path(&buf, spec, &pos)) < 0)
				goto cleanup;

			if (any_left_hand_identifier(base_rev, reference, identifier_len)) {
				if ((error = ensure_base_rev_loaded(&base_rev, &reference, spec, identifier_len, repo, true)) < 0)
					goto cleanup;

				if ((error = handle_colon_syntax(&temp_object, base_rev, git_buf_cstr(&buf))) < 0)
					goto cleanup;
			} else {
				if (*git_buf_cstr(&buf) == '/') {
					if ((error = handle_grep_syntax(&temp_object, repo, NULL, git_buf_cstr(&buf) + 1)) < 0)
						goto cleanup;
				} else {

					/*
					 * TODO: support merge-stage path lookup (":2:Makefile")
					 * and plain index blob lookup (:i-am/a/blob)
					 */
					git_error_set(GIT_ERROR_INVALID, "unimplemented");
					error = GIT_ERROR;
					goto cleanup;
				}
			}

			git_object_free(base_rev);
			base_rev = temp_object;
			break;
		}

		case '@':
			if (spec[pos+1] == '{') {
				git_object *temp_object = NULL;

				if ((error = extract_curly_braces_content(&buf, spec, &pos)) < 0)
					goto cleanup;

				if ((error = ensure_base_rev_is_not_known_yet(base_rev)) < 0)
					goto cleanup;

				if ((error = handle_at_syntax(&temp_object, &reference, spec, identifier_len, repo, git_buf_cstr(&buf))) < 0)
					goto cleanup;

				if (temp_object != NULL)
					base_rev = temp_object;
				break;
			}
			/* fall through */

		default:
			if ((error = ensure_left_hand_identifier_is_not_known_yet(base_rev, reference)) < 0)
				goto cleanup;

			pos++;
			identifier_len++;
		}
	}

	if ((error = ensure_base_rev_loaded(&base_rev, &reference, spec, identifier_len, repo, false)) < 0)
		goto cleanup;

	if (!should_return_reference) {
		git_reference_free(reference);
		reference = NULL;
	}

	*object_out = base_rev;
	*reference_out = reference;
	*identifier_len_out = identifier_len;
	error = 0;

cleanup:
	if (error) {
		if (error == GIT_EINVALIDSPEC)
			git_error_set(GIT_ERROR_INVALID,
				"failed to parse revision specifier - Invalid pattern '%s'", spec);

		git_object_free(base_rev);
		git_reference_free(reference);
	}

	git_buf_dispose(&buf);
	return error;
}