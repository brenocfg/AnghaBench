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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__malloc (size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ p_readlink (char const*,char*,size_t) ; 

__attribute__((used)) static int write_symlink(
	git_oid *id, git_odb *odb, const char *path, size_t link_size)
{
	char *link_data;
	ssize_t read_len;
	int error;

	link_data = git__malloc(link_size);
	GIT_ERROR_CHECK_ALLOC(link_data);

	read_len = p_readlink(path, link_data, link_size);
	if (read_len != (ssize_t)link_size) {
		git_error_set(GIT_ERROR_OS, "failed to create blob: cannot read symlink '%s'", path);
		git__free(link_data);
		return -1;
	}

	error = git_odb_write(id, odb, (void *)link_data, link_size, GIT_OBJECT_BLOB);
	git__free(link_data);
	return error;
}