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
 int /*<<< orphan*/  pwd_allowed_cmd (int /*<<< orphan*/  const*,char const*) ; 
 int pwd_endpwent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pwd_getpwent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pwd_getpwnam (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pwd_getpwuid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pwd_setpassent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pwd_setpwent (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
pwd_command(const char *cmd, const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	int error;

	if (!pwd_allowed_cmd(limits, cmd))
		return (ENOTCAPABLE);

	if (strcmp(cmd, "getpwent") == 0 || strcmp(cmd, "getpwent_r") == 0)
		error = pwd_getpwent(limits, nvlin, nvlout);
	else if (strcmp(cmd, "getpwnam") == 0 || strcmp(cmd, "getpwnam_r") == 0)
		error = pwd_getpwnam(limits, nvlin, nvlout);
	else if (strcmp(cmd, "getpwuid") == 0 || strcmp(cmd, "getpwuid_r") == 0)
		error = pwd_getpwuid(limits, nvlin, nvlout);
	else if (strcmp(cmd, "setpassent") == 0)
		error = pwd_setpassent(limits, nvlin, nvlout);
	else if (strcmp(cmd, "setpwent") == 0)
		error = pwd_setpwent(limits, nvlin, nvlout);
	else if (strcmp(cmd, "endpwent") == 0)
		error = pwd_endpwent(limits, nvlin, nvlout);
	else
		error = EINVAL;

	return (error);
}