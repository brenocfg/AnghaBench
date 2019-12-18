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
struct ccp_cmd_queue {int /*<<< orphan*/  reg_status; } ;

/* Variables and functions */
 unsigned int CMD_Q_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ccp_get_free_slots(struct ccp_cmd_queue *cmd_q)
{
	return CMD_Q_DEPTH(ioread32(cmd_q->reg_status));
}