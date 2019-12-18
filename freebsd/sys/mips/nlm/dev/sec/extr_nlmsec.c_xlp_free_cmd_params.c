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
struct xlp_sec_command {struct xlp_sec_command* hashdest; struct xlp_sec_command* iv; struct xlp_sec_command* paramp; struct xlp_sec_command* ctrlp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct xlp_sec_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xlp_free_cmd_params(struct xlp_sec_command *cmd)
{
	if (cmd->ctrlp != NULL)
		free(cmd->ctrlp, M_DEVBUF);
	if (cmd->paramp != NULL)
		free(cmd->paramp, M_DEVBUF);
	if (cmd->iv != NULL)
		free(cmd->iv, M_DEVBUF);
	if (cmd->hashdest != NULL)
		free(cmd->hashdest, M_DEVBUF);
	if (cmd != NULL)
		free(cmd, M_DEVBUF);
	return;
}