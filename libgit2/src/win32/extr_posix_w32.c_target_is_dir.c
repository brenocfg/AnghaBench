#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_win32_path ;
struct TYPE_6__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_path_apply_relative (TYPE_1__*,char const*) ; 
 scalar_t__ git_path_dirname_r (TYPE_1__*,char const*) ; 
 scalar_t__ git_path_is_absolute (char const*) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool target_is_dir(const char *target, const char *path)
{
	git_buf resolved = GIT_BUF_INIT;
	git_win32_path resolved_w;
	bool isdir = true;

	if (git_path_is_absolute(target))
		git_win32_path_from_utf8(resolved_w, target);
	else if (git_path_dirname_r(&resolved, path) < 0 ||
		 git_path_apply_relative(&resolved, target) < 0 ||
		 git_win32_path_from_utf8(resolved_w, resolved.ptr) < 0)
		goto out;

	isdir = GetFileAttributesW(resolved_w) & FILE_ATTRIBUTE_DIRECTORY;

out:
	git_buf_dispose(&resolved);
	return isdir;
}