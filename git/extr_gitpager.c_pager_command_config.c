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
struct pager_command_config_data {int want; int /*<<< orphan*/  value; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int git_parse_maybe_bool (char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int pager_command_config(const char *var, const char *value, void *vdata)
{
	struct pager_command_config_data *data = vdata;
	const char *cmd;

	if (skip_prefix(var, "pager.", &cmd) && !strcmp(cmd, data->cmd)) {
		int b = git_parse_maybe_bool(value);
		if (b >= 0)
			data->want = b;
		else {
			data->want = 1;
			data->value = xstrdup(value);
		}
	}

	return 0;
}