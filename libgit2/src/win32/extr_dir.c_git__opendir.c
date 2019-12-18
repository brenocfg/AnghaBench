#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_win32_path ;
struct TYPE_5__ {scalar_t__ h; int first; int /*<<< orphan*/  f; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ git__DIR ;

/* Variables and functions */
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 TYPE_1__* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_win32__findfirstfile_filter (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

git__DIR *git__opendir(const char *dir)
{
	git_win32_path filter_w;
	git__DIR *new = NULL;
	size_t dirlen, alloclen;

	if (!dir || !git_win32__findfirstfile_filter(filter_w, dir))
		return NULL;

	dirlen = strlen(dir);

	if (GIT_ADD_SIZET_OVERFLOW(&alloclen, sizeof(*new), dirlen) ||
		GIT_ADD_SIZET_OVERFLOW(&alloclen, alloclen, 1) ||
		!(new = git__calloc(1, alloclen)))
		return NULL;

	memcpy(new->dir, dir, dirlen);

	new->h = FindFirstFileW(filter_w, &new->f);

	if (new->h == INVALID_HANDLE_VALUE) {
		git_error_set(GIT_ERROR_OS, "could not open directory '%s'", dir);
		git__free(new);
		return NULL;
	}

	new->first = 1;
	return new;
}