#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_nlink; } ;
struct TYPE_3__ {scalar_t__ nNumberOfLinks; } ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ BY_HANDLE_FILE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,scalar_t__,int) ; 
 int lstat (char const*,struct stat*) ; 
 int my_GetFileInformationByName (char const*,TYPE_1__*) ; 

int
assertion_file_nlinks(const char *file, int line,
    const char *pathname, int nlinks)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	BY_HANDLE_FILE_INFORMATION bhfi;
	int r;

	assertion_count(file, line);
	r = my_GetFileInformationByName(pathname, &bhfi);
	if (r != 0 && bhfi.nNumberOfLinks == (DWORD)nlinks)
		return (1);
	failure_start(file, line, "File %s has %d links, expected %d",
	    pathname, bhfi.nNumberOfLinks, nlinks);
	failure_finish(NULL);
	return (0);
#else
	struct stat st;
	int r;

	assertion_count(file, line);
	r = lstat(pathname, &st);
	if (r == 0 && (int)st.st_nlink == nlinks)
		return (1);
	failure_start(file, line, "File %s has %d links, expected %d",
	    pathname, st.st_nlink, nlinks);
	failure_finish(NULL);
	return (0);
#endif
}