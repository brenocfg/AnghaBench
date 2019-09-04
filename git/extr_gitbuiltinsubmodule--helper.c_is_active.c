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
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  is_submodule_active (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int is_active(int argc, const char **argv, const char *prefix)
{
	if (argc != 2)
		die("submodule--helper is-active takes exactly 1 argument");

	return !is_submodule_active(the_repository, argv[1]);
}