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
typedef  int /*<<< orphan*/  git_submodule ;

/* Variables and functions */
 char* git_submodule_name (int /*<<< orphan*/ *) ; 
 char* git_submodule_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int print_submod(git_submodule *sm, const char *name, void *payload)
{
	int *count = payload;
	(void)name;

	if (*count == 0)
		printf("# Submodules\n");
	(*count)++;

	printf("# - submodule '%s' at %s\n",
		git_submodule_name(sm), git_submodule_path(sm));

	return 0;
}