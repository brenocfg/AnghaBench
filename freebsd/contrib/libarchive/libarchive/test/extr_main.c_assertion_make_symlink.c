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

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*) ; 
 int /*<<< orphan*/  logprintf (char*,char const*) ; 
 scalar_t__ my_CreateSymbolicLinkA (char const*,char const*,int) ; 
 scalar_t__ symlink (char const*,char const*) ; 

int
assertion_make_symlink(const char *file, int line,
    const char *newpath, const char *linkto)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	int targetIsDir = 0;  /* TODO: Fix this */
	assertion_count(file, line);
	if (my_CreateSymbolicLinkA(newpath, linkto, targetIsDir))
		return (1);
#elif HAVE_SYMLINK
	assertion_count(file, line);
	if (0 == symlink(linkto, newpath))
		return (1);
#endif
	failure_start(file, line, "Could not create symlink");
	logprintf("   New link: %s\n", newpath);
	logprintf("   Old name: %s\n", linkto);
	failure_finish(NULL);
	return(0);
}