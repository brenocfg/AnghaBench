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
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DATA_ENVIRONMENT ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const* const) ; 
 char** local_repo_env ; 
 scalar_t__ strcmp (char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_submodule_repo_env_no_git_dir(struct argv_array *out)
{
	const char * const *var;

	for (var = local_repo_env; *var; var++) {
		if (strcmp(*var, CONFIG_DATA_ENVIRONMENT))
			argv_array_push(out, *var);
	}
}