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
struct child_process {int use_shell; char* trace2_child_class; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  setup_pager_env (int /*<<< orphan*/ *) ; 

void prepare_pager_args(struct child_process *pager_process, const char *pager)
{
	argv_array_push(&pager_process->args, pager);
	pager_process->use_shell = 1;
	setup_pager_env(&pager_process->env_array);
	pager_process->trace2_child_class = "pager";
}