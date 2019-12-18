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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ SetEnvironmentVariableW (int*,int*) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  err_win_to_posix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int*) ; 
 int strlen (char const*) ; 
 int* wcschr (int*,int) ; 
 int /*<<< orphan*/  xutftowcs (int*,char const*,int) ; 

int mingw_putenv(const char *namevalue)
{
	int size;
	wchar_t *wide, *equal;
	BOOL result;

	if (!namevalue || !*namevalue)
		return 0;

	size = strlen(namevalue) * 2 + 1;
	wide = calloc(size, sizeof(wchar_t));
	if (!wide)
		die("Out of memory, (tried to allocate %u wchar_t's)", size);
	xutftowcs(wide, namevalue, size);
	equal = wcschr(wide, L'=');
	if (!equal)
		result = SetEnvironmentVariableW(wide, NULL);
	else {
		*equal = L'\0';
		result = SetEnvironmentVariableW(wide, equal + 1);
	}
	free(wide);

	if (!result)
		errno = err_win_to_posix(GetLastError());

	return result ? 0 : -1;
}