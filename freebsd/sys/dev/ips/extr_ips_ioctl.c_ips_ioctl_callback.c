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
struct TYPE_10__ {int readwrite; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; } ;
typedef  TYPE_2__ ips_ioctl_t ;
struct TYPE_11__ {int /*<<< orphan*/  buffaddr; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ ips_generic_cmd ;
struct TYPE_12__ {TYPE_1__* sc; int /*<<< orphan*/  command_dmamap; int /*<<< orphan*/  id; TYPE_3__* command_buffer; TYPE_2__* arg; } ;
typedef  TYPE_4__ ips_command_t ;
struct TYPE_13__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* ips_issue_cmd ) (TYPE_4__*) ;int /*<<< orphan*/  command_dmatag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int IPS_IOCTL_READ ; 
 int IPS_IOCTL_WRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_set_error (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void ips_ioctl_callback(void *cmdptr, bus_dma_segment_t *segments,int segnum, int error)
{
	ips_command_t *command = cmdptr;
	ips_ioctl_t *ioctl_cmd = command->arg;
	ips_generic_cmd *command_buffer = command->command_buffer;
	if(error){
		ips_set_error(command, error);
		return;
	}
	command_buffer->id = command->id;
	command_buffer->buffaddr = segments[0].ds_addr;
	if(ioctl_cmd->readwrite & IPS_IOCTL_WRITE){
		bus_dmamap_sync(ioctl_cmd->dmatag, ioctl_cmd->dmamap, 
				BUS_DMASYNC_PREWRITE);
	} else if(ioctl_cmd->readwrite & IPS_IOCTL_READ){
		bus_dmamap_sync(ioctl_cmd->dmatag, ioctl_cmd->dmamap, 
				BUS_DMASYNC_PREREAD);
	}
	bus_dmamap_sync(command->sc->command_dmatag, command->command_dmamap, 
			BUS_DMASYNC_PREWRITE);
	command->sc->ips_issue_cmd(command);
}