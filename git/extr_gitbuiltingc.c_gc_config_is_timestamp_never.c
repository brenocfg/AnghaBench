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
typedef  scalar_t__ timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  git_config_get_value (char const*,char const**) ; 
 scalar_t__ parse_expiry_date (char const*,scalar_t__*) ; 

__attribute__((used)) static int gc_config_is_timestamp_never(const char *var)
{
	const char *value;
	timestamp_t expire;

	if (!git_config_get_value(var, &value) && value) {
		if (parse_expiry_date(value, &expire))
			die(_("failed to parse '%s' value '%s'"), var, value);
		return expire == 0;
	}
	return 0;
}