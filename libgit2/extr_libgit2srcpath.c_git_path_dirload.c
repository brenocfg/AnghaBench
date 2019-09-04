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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_path_diriter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_PATH_DIRITER_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 char* git__strndup (char const*,size_t) ; 
 int /*<<< orphan*/  git_path_diriter_free (int /*<<< orphan*/ *) ; 
 int git_path_diriter_fullpath (char const**,size_t*,int /*<<< orphan*/ *) ; 
 int git_path_diriter_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int git_path_diriter_next (int /*<<< orphan*/ *) ; 
 int git_vector_insert (int /*<<< orphan*/ *,char*) ; 

int git_path_dirload(
	git_vector *contents,
	const char *path,
	size_t prefix_len,
	uint32_t flags)
{
	git_path_diriter iter = GIT_PATH_DIRITER_INIT;
	const char *name;
	size_t name_len;
	char *dup;
	int error;

	assert(contents && path);

	if ((error = git_path_diriter_init(&iter, path, flags)) < 0)
		return error;

	while ((error = git_path_diriter_next(&iter)) == 0) {
		if ((error = git_path_diriter_fullpath(&name, &name_len, &iter)) < 0)
			break;

		assert(name_len > prefix_len);

		dup = git__strndup(name + prefix_len, name_len - prefix_len);
		GIT_ERROR_CHECK_ALLOC(dup);

		if ((error = git_vector_insert(contents, dup)) < 0)
			break;
	}

	if (error == GIT_ITEROVER)
		error = 0;

	git_path_diriter_free(&iter);
	return error;
}