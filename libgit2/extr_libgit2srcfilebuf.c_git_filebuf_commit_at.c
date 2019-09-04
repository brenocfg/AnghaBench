#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path_original; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strdup (char const*) ; 
 int git_filebuf_commit (TYPE_1__*) ; 

int git_filebuf_commit_at(git_filebuf *file, const char *path)
{
	git__free(file->path_original);
	file->path_original = git__strdup(path);
	GIT_ERROR_CHECK_ALLOC(file->path_original);

	return git_filebuf_commit(file);
}