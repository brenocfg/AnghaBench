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
 char const* lafe_progname ; 
 char const* strrchr (char const*,char) ; 

void
lafe_setprogname(const char *name, const char *defaultname)
{

	if (name == NULL)
		name = defaultname;
#if defined(_WIN32) && !defined(__CYGWIN__)
	lafe_progname = strrchr(name, '\\');
	if (strrchr(name, '/') > lafe_progname)
#endif
	lafe_progname = strrchr(name, '/');
	if (lafe_progname != NULL)
		lafe_progname++;
	else
		lafe_progname = name;
}