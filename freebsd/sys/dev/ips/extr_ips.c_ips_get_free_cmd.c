#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int state; TYPE_2__* staticcmd; int /*<<< orphan*/  used_commands; int /*<<< orphan*/  free_cmd_list; } ;
typedef  TYPE_1__ ips_softc_t ;
struct TYPE_8__ {int /*<<< orphan*/  command_buffer; } ;
typedef  TYPE_2__ ips_command_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  IPS_COMMAND_LEN ; 
 int IPS_OFFLINE ; 
 int IPS_STATIC_BUSY ; 
 unsigned long IPS_STATIC_FLAG ; 
 int IPS_TIMEOUT ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ips_command (TYPE_2__*) ; 
 int /*<<< orphan*/  next ; 

int ips_get_free_cmd(ips_softc_t *sc, ips_command_t **cmd, unsigned long flags)
{
	ips_command_t *command;

	if(sc->state & IPS_OFFLINE){
		return EIO;
	}
	if ((flags & IPS_STATIC_FLAG) == 0) {
		command = SLIST_FIRST(&sc->free_cmd_list);
		if(!command || (sc->state & IPS_TIMEOUT)){
			return EBUSY;
		}
		SLIST_REMOVE_HEAD(&sc->free_cmd_list, next);
		(sc->used_commands)++;
	} else {
		if (sc->state & IPS_STATIC_BUSY)
			return EAGAIN;
		command = sc->staticcmd;
		sc->state |= IPS_STATIC_BUSY;
	}
	clear_ips_command(command);
	bzero(command->command_buffer, IPS_COMMAND_LEN);
	*cmd = command;
	return 0;
}