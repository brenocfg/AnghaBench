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
struct TYPE_9__ {int /*<<< orphan*/  drivecount; int /*<<< orphan*/  dev; int /*<<< orphan*/  drives; int /*<<< orphan*/  cmd_sema; int /*<<< orphan*/  (* ips_issue_cmd ) (TYPE_4__*) ;int /*<<< orphan*/  command_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  ips_drive_t ;
struct TYPE_10__ {int /*<<< orphan*/  drivecount; int /*<<< orphan*/  drives; } ;
typedef  TYPE_2__ ips_drive_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  buffaddr; int /*<<< orphan*/  id; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ ips_drive_cmd ;
struct TYPE_12__ {TYPE_2__* data_buffer; int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; int /*<<< orphan*/  command_dmamap; int /*<<< orphan*/  id; scalar_t__ command_buffer; TYPE_1__* sc; } ;
typedef  TYPE_4__ ips_command_t ;
struct TYPE_13__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPS_DRIVE_INFO_CMD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  ips_set_error (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ sema_timedwait (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void ips_drive_info_callback(void *cmdptr, bus_dma_segment_t *segments,int segnum, int error)
{
	ips_softc_t *sc;
	ips_command_t *command = cmdptr;
	ips_drive_cmd *command_struct;
	ips_drive_info_t *driveinfo;

	sc = command->sc;
	if(error){
		ips_set_error(command, error);
		printf("ips: error = %d in ips_get_drive_info\n", error);
		return;
	}
	command_struct = (ips_drive_cmd *)command->command_buffer;
	command_struct->command = IPS_DRIVE_INFO_CMD;
	command_struct->id = command->id;
	command_struct->buffaddr = segments[0].ds_addr;

	bus_dmamap_sync(sc->command_dmatag, command->command_dmamap, 
			BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
			BUS_DMASYNC_PREREAD);
	sc->ips_issue_cmd(command);
	if (sema_timedwait(&sc->cmd_sema, 10*hz) != 0) {
		ips_set_error(command, ETIMEDOUT);
		return;
	}

	bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
			BUS_DMASYNC_POSTREAD);
	driveinfo = command->data_buffer;
	memcpy(sc->drives, driveinfo->drives, sizeof(ips_drive_t) * 8);	
	sc->drivecount = driveinfo->drivecount;
	device_printf(sc->dev, "logical drives: %d\n",sc->drivecount);
}