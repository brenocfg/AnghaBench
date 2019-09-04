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
struct config_include_data {int (* fn ) (char const*,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  opts; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int handle_path_include (char const*,struct config_include_data*) ; 
 scalar_t__ include_condition_is_true (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (char const*,char const*,int /*<<< orphan*/ ) ; 

int git_config_include(const char *var, const char *value, void *data)
{
	struct config_include_data *inc = data;
	const char *cond, *key;
	int cond_len;
	int ret;

	/*
	 * Pass along all values, including "include" directives; this makes it
	 * possible to query information on the includes themselves.
	 */
	ret = inc->fn(var, value, inc->data);
	if (ret < 0)
		return ret;

	if (!strcmp(var, "include.path"))
		ret = handle_path_include(value, inc);

	if (!parse_config_key(var, "includeif", &cond, &cond_len, &key) &&
	    (cond && include_condition_is_true(inc->opts, cond, cond_len)) &&
	    !strcmp(key, "path"))
		ret = handle_path_include(value, inc);

	return ret;
}