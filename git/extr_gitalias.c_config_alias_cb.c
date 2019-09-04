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
struct config_alias_data {scalar_t__ list; int /*<<< orphan*/  v; scalar_t__ alias; } ;

/* Variables and functions */
 int git_config_string (char const**,char const*,char const*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcasecmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  string_list_append (scalar_t__,char const*) ; 

__attribute__((used)) static int config_alias_cb(const char *key, const char *value, void *d)
{
	struct config_alias_data *data = d;
	const char *p;

	if (!skip_prefix(key, "alias.", &p))
		return 0;

	if (data->alias) {
		if (!strcasecmp(p, data->alias))
			return git_config_string((const char **)&data->v,
						 key, value);
	} else if (data->list) {
		string_list_append(data->list, p);
	}

	return 0;
}