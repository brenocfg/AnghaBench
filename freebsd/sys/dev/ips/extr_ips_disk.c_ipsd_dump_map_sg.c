#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* ips_poll_cmd ) (TYPE_4__*) ;int /*<<< orphan*/  (* ips_issue_cmd ) (TYPE_4__*) ;int /*<<< orphan*/  command_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;
struct TYPE_11__ {int addr; int len; } ;
typedef  TYPE_2__ ips_sg_element_t ;
struct TYPE_12__ {int segnum; int buffaddr; int length; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ ips_io_cmd ;
struct TYPE_13__ {int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; int /*<<< orphan*/  command_dmamap; scalar_t__ command_phys_addr; scalar_t__ command_buffer; TYPE_1__* sc; } ;
typedef  TYPE_4__ ips_command_t ;
struct TYPE_14__ {int ds_addr; int ds_len; } ;
typedef  TYPE_5__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int IPS_BLKSIZE ; 
 int IPS_COMMAND_LEN ; 
 int /*<<< orphan*/  IPS_SG_WRITE_CMD ; 
 int /*<<< orphan*/  IPS_WRITE_CMD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_set_error (TYPE_4__*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

__attribute__((used)) static void
ipsd_dump_map_sg(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	ips_softc_t *sc;
	ips_command_t *command;
	ips_sg_element_t *sg_list;
	ips_io_cmd *command_struct;
	int i, length;

	command = (ips_command_t *)arg;
	sc = command->sc;
	length = 0;

	if (error) {
		printf("ipsd_dump_map_sg: error %d\n", error);
		ips_set_error(command, error);
		return;
	}

	command_struct = (ips_io_cmd *)command->command_buffer;

	if (nsegs != 1) {
		command_struct->segnum = nsegs;
		sg_list = (ips_sg_element_t *)((uint8_t *)
		    command->command_buffer + IPS_COMMAND_LEN);
		for (i = 0; i < nsegs; i++) {
			sg_list[i].addr = segs[i].ds_addr;
			sg_list[i].len = segs[i].ds_len;
			length += segs[i].ds_len;
		}
		command_struct->buffaddr =
		    (uint32_t)command->command_phys_addr + IPS_COMMAND_LEN;
		command_struct->command = IPS_SG_WRITE_CMD;
	} else {
		command_struct->buffaddr = segs[0].ds_addr;
		length = segs[0].ds_len;
		command_struct->segnum = 0;
		command_struct->command = IPS_WRITE_CMD;
	}

	length = (length + IPS_BLKSIZE - 1) / IPS_BLKSIZE;
	command_struct->length = length;
	bus_dmamap_sync(sc->command_dmatag, command->command_dmamap,
	    BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(command->data_dmatag, command->data_dmamap,
	    BUS_DMASYNC_PREWRITE);

	sc->ips_issue_cmd(command);
	sc->ips_poll_cmd(command);
	return;
}