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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCAPABLE ; 
 int /*<<< orphan*/  grp_allowed_cmd (int /*<<< orphan*/  const*,char const*) ; 
 int grp_endgrent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int grp_getgrent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int grp_getgrgid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int grp_getgrnam (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int grp_setgrent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int grp_setgroupent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
grp_command(const char *cmd, const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	int error;

	if (!grp_allowed_cmd(limits, cmd))
		return (ENOTCAPABLE);

	if (strcmp(cmd, "getgrent") == 0 || strcmp(cmd, "getgrent_r") == 0)
		error = grp_getgrent(limits, nvlin, nvlout);
	else if (strcmp(cmd, "getgrnam") == 0 || strcmp(cmd, "getgrnam_r") == 0)
		error = grp_getgrnam(limits, nvlin, nvlout);
	else if (strcmp(cmd, "getgrgid") == 0 || strcmp(cmd, "getgrgid_r") == 0)
		error = grp_getgrgid(limits, nvlin, nvlout);
	else if (strcmp(cmd, "setgroupent") == 0)
		error = grp_setgroupent(limits, nvlin, nvlout);
	else if (strcmp(cmd, "setgrent") == 0)
		error = grp_setgrent(limits, nvlin, nvlout);
	else if (strcmp(cmd, "endgrent") == 0)
		error = grp_endgrent(limits, nvlin, nvlout);
	else
		error = EINVAL;

	return (error);
}