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
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_dl_iterate_phdr () ; 
 int /*<<< orphan*/  test_dlclose () ; 
 int /*<<< orphan*/  test_dlopen () ; 

int
main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	if (strcmp(argv[1], "dl_iterate_phdr") == 0)
		test_dl_iterate_phdr();
	if (strcmp(argv[1], "dlopen") == 0)
		test_dlopen();
	if (strcmp(argv[1], "dlclose") == 0)
		test_dlclose();
	return 1;
}