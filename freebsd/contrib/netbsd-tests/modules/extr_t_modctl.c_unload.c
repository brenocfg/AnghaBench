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
 int /*<<< orphan*/  MODCTL_UNLOAD ; 
 int /*<<< orphan*/  __UNCONST (char const*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  check_permission () ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int modctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static int
unload(const char *name, bool fatal)
{
	int err;

	check_permission();
	printf("Unloading module %s\n", name);
	errno = err = 0;

	if (modctl(MODCTL_UNLOAD, __UNCONST(name)) == -1) {
		err = errno;
		fprintf(stderr, "modctl(MODCTL_UNLOAD, %s) failed: %s\n",
		    name, strerror(err));
		if (fatal)
			atf_tc_fail("Module unload failed");
	}
	return err;
}