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
 int /*<<< orphan*/  link (char const*,char const*) ; 
 int /*<<< orphan*/  logprintf (char*,char const*) ; 
 int my_CreateHardLinkA (char const*,char const*) ; 

int
assertion_make_hardlink(const char *file, int line,
    const char *newpath, const char *linkto)
{
	int succeeded;

	assertion_count(file, line);
#if defined(_WIN32) && !defined(__CYGWIN__)
	succeeded = my_CreateHardLinkA(newpath, linkto);
#elif HAVE_LINK
	succeeded = !link(linkto, newpath);
#else
	succeeded = 0;
#endif
	if (succeeded)
		return (1);
	failure_start(file, line, "Could not create hardlink");
	logprintf("   New link: %s\n", newpath);
	logprintf("   Old name: %s\n", linkto);
	failure_finish(NULL);
	return(0);
}