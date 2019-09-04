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
struct merge_options {void* merge_detect_rename; void* diff_detect_rename; int /*<<< orphan*/  merge_rename_limit; int /*<<< orphan*/  diff_rename_limit; int /*<<< orphan*/  verbosity; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char*,char**) ; 
 void* git_config_rename (char*,char*) ; 
 int /*<<< orphan*/  git_xmerge_config ; 

__attribute__((used)) static void merge_recursive_config(struct merge_options *o)
{
	char *value = NULL;
	git_config_get_int("merge.verbosity", &o->verbosity);
	git_config_get_int("diff.renamelimit", &o->diff_rename_limit);
	git_config_get_int("merge.renamelimit", &o->merge_rename_limit);
	if (!git_config_get_string("diff.renames", &value)) {
		o->diff_detect_rename = git_config_rename("diff.renames", value);
		free(value);
	}
	if (!git_config_get_string("merge.renames", &value)) {
		o->merge_detect_rename = git_config_rename("merge.renames", value);
		free(value);
	}
	git_config(git_xmerge_config, NULL);
}