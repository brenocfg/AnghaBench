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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_merge_preference_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_MERGE_PREFERENCE_FASTFORWARD_ONLY ; 
 int /*<<< orphan*/  GIT_MERGE_PREFERENCE_NONE ; 
 int /*<<< orphan*/  GIT_MERGE_PREFERENCE_NO_FASTFORWARD ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_config_parse_bool (int*,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int merge_preference(git_merge_preference_t *out, git_repository *repo)
{
	git_config *config;
	const char *value;
	int bool_value, error = 0;

	*out = GIT_MERGE_PREFERENCE_NONE;

	if ((error = git_repository_config_snapshot(&config, repo)) < 0)
		goto done;

	if ((error = git_config_get_string(&value, config, "merge.ff")) < 0) {
		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			error = 0;
		}

		goto done;
	}

	if (git_config_parse_bool(&bool_value, value) == 0) {
		if (!bool_value)
			*out |= GIT_MERGE_PREFERENCE_NO_FASTFORWARD;
	} else {
		if (strcasecmp(value, "only") == 0)
			*out |= GIT_MERGE_PREFERENCE_FASTFORWARD_ONLY;
	}

done:
	git_config_free(config);
	return error;
}