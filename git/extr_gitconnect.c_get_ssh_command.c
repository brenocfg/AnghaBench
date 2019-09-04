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

/* Variables and functions */
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_config_get_string_const (char*,char const**) ; 

__attribute__((used)) static const char *get_ssh_command(void)
{
	const char *ssh;

	if ((ssh = getenv("GIT_SSH_COMMAND")))
		return ssh;

	if (!git_config_get_string_const("core.sshcommand", &ssh))
		return ssh;

	return NULL;
}