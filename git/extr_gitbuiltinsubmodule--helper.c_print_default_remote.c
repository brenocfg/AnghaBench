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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_default_remote () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int print_default_remote(int argc, const char **argv, const char *prefix)
{
	char *remote;

	if (argc != 1)
		die(_("submodule--helper print-default-remote takes no arguments"));

	remote = get_default_remote();
	if (remote)
		printf("%s\n", remote);

	free(remote);
	return 0;
}