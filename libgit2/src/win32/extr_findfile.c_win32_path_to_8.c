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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  git_win32_utf8_path ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path_mkposix (int /*<<< orphan*/ ) ; 
 scalar_t__ git_win32_path_to_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int win32_path_to_8(git_buf *dest, const wchar_t *src)
{
	git_win32_utf8_path utf8_path;

	if (git_win32_path_to_utf8(utf8_path, src) < 0) {
		git_error_set(GIT_ERROR_OS, "unable to convert path to UTF-8");
		return -1;
	}

	/* Convert backslashes to forward slashes */
	git_path_mkposix(utf8_path);

	return git_buf_sets(dest, utf8_path);
}