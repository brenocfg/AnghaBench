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
struct xlp_rsa_command {struct xlp_rsa_command* rsasrc; int /*<<< orphan*/ * krp; } ;
typedef  int /*<<< orphan*/  nlm_rsa_ucode_data ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  contigfree (struct xlp_rsa_command*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct xlp_rsa_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xlp_free_cmd_params(struct xlp_rsa_command *cmd)
{

	if (cmd == NULL)
		return;
	if (cmd->rsasrc != NULL) {
		if (cmd->krp == NULL) /* Micro code load */
			contigfree(cmd->rsasrc, sizeof(nlm_rsa_ucode_data),
			    M_DEVBUF);
		else
			free(cmd->rsasrc, M_DEVBUF);
	}
	free(cmd, M_DEVBUF);
}