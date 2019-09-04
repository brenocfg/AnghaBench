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
typedef  int /*<<< orphan*/  timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int config_error_nonbool (char const*) ; 
 int error (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ parse_expiry_date (char const*,int /*<<< orphan*/ *) ; 

int git_config_expiry_date(timestamp_t *timestamp, const char *var, const char *value)
{
	if (!value)
		return config_error_nonbool(var);
	if (parse_expiry_date(value, timestamp))
		return error(_("'%s' for '%s' is not a valid timestamp"),
			     value, var);
	return 0;
}