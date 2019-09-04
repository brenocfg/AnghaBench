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
typedef  enum missing_commit_check_level { ____Placeholder_missing_commit_check_level } missing_commit_check_level ;

/* Variables and functions */
 int MISSING_COMMIT_CHECK_ERROR ; 
 int MISSING_COMMIT_CHECK_IGNORE ; 
 int MISSING_COMMIT_CHECK_WARN ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ git_config_get_value (char*,char const**) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static enum missing_commit_check_level get_missing_commit_check_level(void)
{
	const char *value;

	if (git_config_get_value("rebase.missingcommitscheck", &value) ||
			!strcasecmp("ignore", value))
		return MISSING_COMMIT_CHECK_IGNORE;
	if (!strcasecmp("warn", value))
		return MISSING_COMMIT_CHECK_WARN;
	if (!strcasecmp("error", value))
		return MISSING_COMMIT_CHECK_ERROR;
	warning(_("unrecognized setting %s for option "
		  "rebase.missingCommitsCheck. Ignoring."), value);
	return MISSING_COMMIT_CHECK_IGNORE;
}