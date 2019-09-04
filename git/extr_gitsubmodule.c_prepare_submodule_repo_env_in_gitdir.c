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
 int /*<<< orphan*/  GIT_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env_no_git_dir (struct argv_array*) ; 

__attribute__((used)) static void prepare_submodule_repo_env_in_gitdir(struct argv_array *out)
{
	prepare_submodule_repo_env_no_git_dir(out);
	argv_array_pushf(out, "%s=.", GIT_DIR_ENVIRONMENT);
}