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
typedef  int wchar_t ;
typedef  int* git_win32_path ;

/* Variables and functions */
 int GIT_WIN_PATH_UTF16 ; 
 int GetShortPathNameW (int*,int*,int) ; 
 char* git__malloc (int) ; 
 int git__utf16_to_8 (char*,int,int*) ; 
 scalar_t__ git_win32_path_from_utf8 (int*,char const*) ; 

char *git_win32_path_8dot3_name(const char *path)
{
	git_win32_path longpath, shortpath;
	wchar_t *start;
	char *shortname;
	int len, namelen = 1;

	if (git_win32_path_from_utf8(longpath, path) < 0)
		return NULL;

	len = GetShortPathNameW(longpath, shortpath, GIT_WIN_PATH_UTF16);

	while (len && shortpath[len-1] == L'\\')
		shortpath[--len] = L'\0';

	if (len == 0 || len >= GIT_WIN_PATH_UTF16)
		return NULL;

	for (start = shortpath + (len - 1);
		start > shortpath && *(start-1) != '/' && *(start-1) != '\\';
		start--)
		namelen++;

	/* We may not have actually been given a short name.  But if we have,
	 * it will be in the ASCII byte range, so we don't need to worry about
	 * multi-byte sequences and can allocate naively.
	 */
	if (namelen > 12 || (shortname = git__malloc(namelen + 1)) == NULL)
		return NULL;

	if ((len = git__utf16_to_8(shortname, namelen + 1, start)) < 0)
		return NULL;

	return shortname;
}