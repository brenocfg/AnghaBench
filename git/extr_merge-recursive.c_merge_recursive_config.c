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
struct merge_options {int /*<<< orphan*/  detect_directory_renames; void* detect_renames; int /*<<< orphan*/  rename_limit; int /*<<< orphan*/  verbosity; } ;

/* Variables and functions */
 int /*<<< orphan*/  MERGE_DIRECTORY_RENAMES_CONFLICT ; 
 int /*<<< orphan*/  MERGE_DIRECTORY_RENAMES_NONE ; 
 int /*<<< orphan*/  MERGE_DIRECTORY_RENAMES_TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char*,char**) ; 
 void* git_config_rename (char*,char*) ; 
 int git_parse_maybe_bool (char*) ; 
 int /*<<< orphan*/  git_xmerge_config ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static void merge_recursive_config(struct merge_options *opt)
{
	char *value = NULL;
	git_config_get_int("merge.verbosity", &opt->verbosity);
	git_config_get_int("diff.renamelimit", &opt->rename_limit);
	git_config_get_int("merge.renamelimit", &opt->rename_limit);
	if (!git_config_get_string("diff.renames", &value)) {
		opt->detect_renames = git_config_rename("diff.renames", value);
		free(value);
	}
	if (!git_config_get_string("merge.renames", &value)) {
		opt->detect_renames = git_config_rename("merge.renames", value);
		free(value);
	}
	if (!git_config_get_string("merge.directoryrenames", &value)) {
		int boolval = git_parse_maybe_bool(value);
		if (0 <= boolval) {
			opt->detect_directory_renames = boolval ?
				MERGE_DIRECTORY_RENAMES_TRUE :
				MERGE_DIRECTORY_RENAMES_NONE;
		} else if (!strcasecmp(value, "conflict")) {
			opt->detect_directory_renames =
				MERGE_DIRECTORY_RENAMES_CONFLICT;
		} /* avoid erroring on values from future versions of git */
		free(value);
	}
	git_config(git_xmerge_config, NULL);
}