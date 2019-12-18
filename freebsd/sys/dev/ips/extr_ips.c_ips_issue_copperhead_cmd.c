#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int timeout; TYPE_3__* sc; int /*<<< orphan*/  command_phys_addr; int /*<<< orphan*/  (* callback ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ips_command_t ;
struct TYPE_9__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPPER_CMD_START ; 
 int /*<<< orphan*/  COPPER_REG_CCCR ; 
 int /*<<< orphan*/  COPPER_REG_CCSAR ; 
 int COPPER_SEM_BIT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int IPS_OFFLINE ; 
 int ips_read_4 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_set_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_write_2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_write_4 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void ips_issue_copperhead_cmd(ips_command_t *command)
{
	int i;
	/* hmmm, is there a cleaner way to do this? */
	if(command->sc->state & IPS_OFFLINE){
		ips_set_error(command, EINVAL);
		command->callback(command);
		return;
	}
	command->timeout = 10;
	for(i = 0; ips_read_4(command->sc, COPPER_REG_CCCR) & COPPER_SEM_BIT;
	    i++ ){
		if( i == 20){
printf("sem bit still set, can't send a command\n");
			return;
		}
		DELAY(500);/* need to do a delay here */
	}
	ips_write_4(command->sc, COPPER_REG_CCSAR, command->command_phys_addr);
	ips_write_2(command->sc, COPPER_REG_CCCR, COPPER_CMD_START);
}