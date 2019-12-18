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
struct ccp_tasklet_data {int /*<<< orphan*/  completion; struct ccp_cmd* cmd; } ;
struct ccp_cmd {int /*<<< orphan*/  ret; int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccp_do_cmd_complete(unsigned long data)
{
	struct ccp_tasklet_data *tdata = (struct ccp_tasklet_data *)data;
	struct ccp_cmd *cmd = tdata->cmd;

	cmd->callback(cmd->data, cmd->ret);

	complete(&tdata->completion);
}