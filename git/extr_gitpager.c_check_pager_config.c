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
struct pager_command_config_data {char const* cmd; int want; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  pager_command_config ; 
 int /*<<< orphan*/ * pager_program ; 
 int /*<<< orphan*/  read_early_config (int /*<<< orphan*/ ,struct pager_command_config_data*) ; 

int check_pager_config(const char *cmd)
{
	struct pager_command_config_data data;

	data.cmd = cmd;
	data.want = -1;
	data.value = NULL;

	read_early_config(pager_command_config, &data);

	if (data.value)
		pager_program = data.value;
	return data.want;
}