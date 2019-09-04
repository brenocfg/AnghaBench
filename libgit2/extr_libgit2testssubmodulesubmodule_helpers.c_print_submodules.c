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
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,unsigned int) ; 
 int /*<<< orphan*/  git_submodule_location (unsigned int*,int /*<<< orphan*/ *) ; 
 char* git_submodule_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int print_submodules(git_submodule *sm, const char *name, void *p)
{
	unsigned int loc = 0;
	GIT_UNUSED(p);
	git_submodule_location(&loc, sm);
	fprintf(stderr, "# submodule %s (at %s) flags %x\n",
		name, git_submodule_path(sm), loc);
	return 0;
}