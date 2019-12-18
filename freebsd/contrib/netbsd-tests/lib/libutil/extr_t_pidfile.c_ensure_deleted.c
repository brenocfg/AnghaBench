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
 int /*<<< orphan*/  R_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ in_child ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static void
ensure_deleted(const char *path)
{
	printf("Ensuring pidfile %s does not exist any more\n", path);
	if (access(path, R_OK) != -1) {
		unlink(path);
		if (in_child)
			errx(EXIT_FAILURE, "The pidfile %s was not deleted",
			    path);
		else
			atf_tc_fail("The pidfile %s was not deleted", path);
	}
}