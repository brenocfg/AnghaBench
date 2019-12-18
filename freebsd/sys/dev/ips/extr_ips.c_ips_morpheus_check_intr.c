#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_11__ {TYPE_4__* commandarray; int /*<<< orphan*/  dev; } ;
typedef  TYPE_3__ ips_softc_t ;
struct TYPE_10__ {int value; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* callback ) (TYPE_4__*) ;scalar_t__ timeout; TYPE_2__ status; } ;
typedef  TYPE_4__ ips_command_t ;
struct TYPE_9__ {int command_id; } ;
struct TYPE_13__ {int value; TYPE_1__ fields; } ;
typedef  TYPE_5__ ips_cmd_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int MORPHEUS_BIT_CMD_IRQ ; 
 int /*<<< orphan*/  MORPHEUS_REG_OISR ; 
 int /*<<< orphan*/  MORPHEUS_REG_OQPR ; 
 int /*<<< orphan*/  PRINTF (int,char*,int) ; 
 void* ips_read_4 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static __inline int ips_morpheus_check_intr(ips_softc_t *sc)
{
	int cmdnumber;
	ips_cmd_status_t status;
	ips_command_t *command;
	int found = 0;
	u_int32_t oisr;

	oisr = ips_read_4(sc, MORPHEUS_REG_OISR);
	PRINTF(9, "interrupt registers out:%x\n", oisr);
	if(!(oisr & MORPHEUS_BIT_CMD_IRQ)){
		DEVICE_PRINTF(2,sc->dev, "got a non-command irq\n");
		return (0);	
	}
	while((status.value = ips_read_4(sc, MORPHEUS_REG_OQPR)) != 0xffffffff){
		cmdnumber = status.fields.command_id;
		command = &sc->commandarray[cmdnumber];
		command->status.value = status.value;
		command->timeout = 0;
		command->callback(command);

		found = 1;
	}
        return (found);
}