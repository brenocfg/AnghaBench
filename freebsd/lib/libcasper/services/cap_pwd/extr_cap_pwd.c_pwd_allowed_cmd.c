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
 int nvlist_exists_null (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static bool
pwd_allowed_cmd(const nvlist_t *limits, const char *cmd)
{

	if (limits == NULL)
		return (true);

	/*
	 * If no limit was set on allowed commands, then all commands
	 * are allowed.
	 */
	if (!nvlist_exists_nvlist(limits, "cmds"))
		return (true);

	limits = nvlist_get_nvlist(limits, "cmds");
	return (nvlist_exists_null(limits, cmd));
}