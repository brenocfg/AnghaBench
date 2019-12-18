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
struct ecore_queue_state_params {int cmd; } ;
struct ecore_queue_sp_obj {int /*<<< orphan*/  pending; } ;
typedef  enum ecore_queue_cmd { ____Placeholder_ecore_queue_cmd } ecore_queue_cmd ;

/* Variables and functions */
 int ECORE_Q_CMD_ACTIVATE ; 
 int ECORE_Q_CMD_DEACTIVATE ; 
 int ECORE_Q_CMD_UPDATE ; 
 int /*<<< orphan*/  ECORE_SET_BIT (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecore_queue_set_pending(struct ecore_queue_sp_obj *obj,
				   struct ecore_queue_state_params *params)
{
	enum ecore_queue_cmd cmd = params->cmd, bit;

	/* ACTIVATE and DEACTIVATE commands are implemented on top of
	 * UPDATE command.
	 */
	if ((cmd == ECORE_Q_CMD_ACTIVATE) ||
	    (cmd == ECORE_Q_CMD_DEACTIVATE))
		bit = ECORE_Q_CMD_UPDATE;
	else
		bit = cmd;

	ECORE_SET_BIT(bit, &obj->pending);
	return bit;
}