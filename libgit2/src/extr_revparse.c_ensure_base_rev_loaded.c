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
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_put (int /*<<< orphan*/ *,char const*,size_t) ; 
 int object_from_reference (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int revparse_lookup_object (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ensure_base_rev_loaded(git_object **object, git_reference **reference, const char *spec, size_t identifier_len, git_repository *repo, bool allow_empty_identifier)
{
	int error;
	git_buf identifier = GIT_BUF_INIT;

	if (*object != NULL)
		return 0;

	if (*reference != NULL)
		return object_from_reference(object, *reference);

	if (!allow_empty_identifier && identifier_len == 0)
		return GIT_EINVALIDSPEC;

	if (git_buf_put(&identifier, spec, identifier_len) < 0)
		return -1;

	error = revparse_lookup_object(object, reference, repo, git_buf_cstr(&identifier));
	git_buf_dispose(&identifier);

	return error;
}