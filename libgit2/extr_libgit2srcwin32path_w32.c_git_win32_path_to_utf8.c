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
typedef  char* git_win32_utf8_path ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_WIN_PATH_UTF8 ; 
 int git__utf16_to_8 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_path_mkposix (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ path__is_nt_namespace (int /*<<< orphan*/  const*) ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/  const*,char*,int) ; 

int git_win32_path_to_utf8(git_win32_utf8_path dest, const wchar_t *src)
{
	char *out = dest;
	int len;

	/* Strip NT namespacing "\\?\" */
	if (path__is_nt_namespace(src)) {
		src += 4;

		/* "\\?\UNC\server\share" -> "\\server\share" */
		if (wcsncmp(src, L"UNC\\", 4) == 0) {
			src += 4;

			memcpy(dest, "\\\\", 2);
			out = dest + 2;
		}
	}

	if ((len = git__utf16_to_8(out, GIT_WIN_PATH_UTF8, src)) < 0)
		return len;

	git_path_mkposix(dest);

	return len;
}