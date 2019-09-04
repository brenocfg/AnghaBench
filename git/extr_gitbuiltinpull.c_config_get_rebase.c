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
struct branch {int /*<<< orphan*/  name; } ;
typedef  enum rebase_type { ____Placeholder_rebase_type } rebase_type ;

/* Variables and functions */
 int REBASE_FALSE ; 
 struct branch* branch_get (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 int parse_config_rebase (char*,char const*,int) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum rebase_type config_get_rebase(void)
{
	struct branch *curr_branch = branch_get("HEAD");
	const char *value;

	if (curr_branch) {
		char *key = xstrfmt("branch.%s.rebase", curr_branch->name);

		if (!git_config_get_value(key, &value)) {
			enum rebase_type ret = parse_config_rebase(key, value, 1);
			free(key);
			return ret;
		}

		free(key);
	}

	if (!git_config_get_value("pull.rebase", &value))
		return parse_config_rebase("pull.rebase", value, 1);

	return REBASE_FALSE;
}