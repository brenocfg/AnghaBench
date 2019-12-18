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
 int fileargs_command_lstat (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fileargs_command_open (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
fileargs_command(const char *cmd, const nvlist_t *limits,
    nvlist_t *nvlin, nvlist_t *nvlout)
{

	if (strcmp(cmd, "open") == 0)
		return (fileargs_command_open(limits, nvlin, nvlout));

	if (strcmp(cmd, "lstat") == 0)
		return (fileargs_command_lstat(limits, nvlin, nvlout));

	return (EINVAL);
}