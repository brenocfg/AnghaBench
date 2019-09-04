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
struct fsck_gitmodules_data {int /*<<< orphan*/  obj; int /*<<< orphan*/  options; int /*<<< orphan*/  ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_NAME ; 
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_PATH ; 
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_URL ; 
 scalar_t__ check_submodule_name (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ looks_like_command_line_option (char const*) ; 
 scalar_t__ parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* xmemdupz (char const*,int) ; 

__attribute__((used)) static int fsck_gitmodules_fn(const char *var, const char *value, void *vdata)
{
	struct fsck_gitmodules_data *data = vdata;
	const char *subsection, *key;
	int subsection_len;
	char *name;

	if (parse_config_key(var, "submodule", &subsection, &subsection_len, &key) < 0 ||
	    !subsection)
		return 0;

	name = xmemdupz(subsection, subsection_len);
	if (check_submodule_name(name) < 0)
		data->ret |= report(data->options, data->obj,
				    FSCK_MSG_GITMODULES_NAME,
				    "disallowed submodule name: %s",
				    name);
	if (!strcmp(key, "url") && value &&
	    looks_like_command_line_option(value))
		data->ret |= report(data->options, data->obj,
				    FSCK_MSG_GITMODULES_URL,
				    "disallowed submodule url: %s",
				    value);
	if (!strcmp(key, "path") && value &&
	    looks_like_command_line_option(value))
		data->ret |= report(data->options, data->obj,
				    FSCK_MSG_GITMODULES_PATH,
				    "disallowed submodule path: %s",
				    value);
	free(name);

	return 0;
}