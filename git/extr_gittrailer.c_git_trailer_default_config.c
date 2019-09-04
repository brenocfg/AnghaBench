#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  if_missing; int /*<<< orphan*/  if_exists; int /*<<< orphan*/  where; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__ default_conf_info ; 
 int /*<<< orphan*/  separators ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ trailer_set_if_exists (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ trailer_set_if_missing (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ trailer_set_where (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int git_trailer_default_config(const char *conf_key, const char *value, void *cb)
{
	const char *trailer_item, *variable_name;

	if (!skip_prefix(conf_key, "trailer.", &trailer_item))
		return 0;

	variable_name = strrchr(trailer_item, '.');
	if (!variable_name) {
		if (!strcmp(trailer_item, "where")) {
			if (trailer_set_where(&default_conf_info.where,
					      value) < 0)
				warning(_("unknown value '%s' for key '%s'"),
					value, conf_key);
		} else if (!strcmp(trailer_item, "ifexists")) {
			if (trailer_set_if_exists(&default_conf_info.if_exists,
						  value) < 0)
				warning(_("unknown value '%s' for key '%s'"),
					value, conf_key);
		} else if (!strcmp(trailer_item, "ifmissing")) {
			if (trailer_set_if_missing(&default_conf_info.if_missing,
						   value) < 0)
				warning(_("unknown value '%s' for key '%s'"),
					value, conf_key);
		} else if (!strcmp(trailer_item, "separators")) {
			separators = xstrdup(value);
		}
	}
	return 0;
}