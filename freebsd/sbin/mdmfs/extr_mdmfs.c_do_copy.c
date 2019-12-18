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
 int chdir (char const*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int run (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void
do_copy(const char *mtpoint, const char *skel)
{
	int rv;

	rv = chdir(skel);
	if (rv != 0)
		err(1, "chdir to %s", skel);
	rv = run(NULL, "/bin/pax -rw -pe . %s", mtpoint);
	if (rv != 0)
		errx(1, "skel copy failed");
}