#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_7__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_SYMREF ; 
 int /*<<< orphan*/  git__free (char*) ; 
 scalar_t__ git__strncmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 int git_futils_readbuffer (TYPE_1__*,char const*) ; 
 char* git_path_basename (char const*) ; 
 int /*<<< orphan*/ * git_reference__alloc_symbolic (char*,scalar_t__) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int git_reference__read_head(
	git_reference **out,
	git_repository *repo,
	const char *path)
{
	git_buf reference = GIT_BUF_INIT;
	char *name = NULL;
	int error;

	if ((error = git_futils_readbuffer(&reference, path)) < 0)
		goto out;
	git_buf_rtrim(&reference);

	if (git__strncmp(reference.ptr, GIT_SYMREF, strlen(GIT_SYMREF)) == 0) {
		git_buf_consume(&reference, reference.ptr + strlen(GIT_SYMREF));

		name = git_path_basename(path);

		if ((*out = git_reference__alloc_symbolic(name, reference.ptr)) == NULL) {
			error = -1;
			goto out;
		}
	} else {
		if ((error = git_reference_lookup(out, repo, reference.ptr)) < 0)
			goto out;
	}

out:
	git__free(name);
	git_buf_dispose(&reference);

	return error;
}