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
struct repository_format {int /*<<< orphan*/  work_tree; int /*<<< orphan*/  is_bare; } ;

/* Variables and functions */
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int read_worktree_config(const char *var, const char *value, void *vdata)
{
	struct repository_format *data = vdata;

	if (strcmp(var, "core.bare") == 0) {
		data->is_bare = git_config_bool(var, value);
	} else if (strcmp(var, "core.worktree") == 0) {
		if (!value)
			return config_error_nonbool(var);
		free(data->work_tree);
		data->work_tree = xstrdup(value);
	}
	return 0;
}