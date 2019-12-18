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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  _PATH_VARRUN ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 char const* getprogname () ; 
 scalar_t__ in_child ; 

__attribute__((used)) static char *
generate_varrun_pidfile(const char *basename)
{
	char *path;

	if (asprintf(&path, "%s%s.pid", _PATH_VARRUN,
	    basename == NULL ? getprogname() : basename) == -1) {
		if (in_child)
			errx(EXIT_FAILURE, "Cannot allocate memory for path");
		else
			atf_tc_fail("Cannot allocate memory for path");
	}

	return path;
}