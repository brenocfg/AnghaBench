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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct bio {int /*<<< orphan*/  bio_pblkno; scalar_t__ bio_driver1; int /*<<< orphan*/  bio_error; int /*<<< orphan*/  bio_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ips_issue_cmd ) (TYPE_4__*) ;int /*<<< orphan*/  command_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;
struct TYPE_11__ {int addr; int len; } ;
typedef  TYPE_2__ ips_sg_element_t ;
struct TYPE_12__ {uintptr_t drivenum; int segnum; int buffaddr; int length; int /*<<< orphan*/  lba; int /*<<< orphan*/  command; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ ips_io_cmd ;
struct TYPE_13__ {int /*<<< orphan*/  id; int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; int /*<<< orphan*/  command_dmamap; scalar_t__ command_phys_addr; scalar_t__ command_buffer; TYPE_1__* sc; struct bio* arg; } ;
typedef  TYPE_4__ ips_command_t ;
struct TYPE_14__ {int ds_addr; int ds_len; } ;
typedef  TYPE_5__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int IPS_BLKSIZE ; 
 int IPS_COMMAND_LEN ; 
 int /*<<< orphan*/  IPS_READ_CMD ; 
 int /*<<< orphan*/  IPS_SG_READ_CMD ; 
 int /*<<< orphan*/  IPS_SG_WRITE_CMD ; 
 int /*<<< orphan*/  IPS_WRITE_CMD ; 
 int /*<<< orphan*/  PRINTF (int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_insert_free_cmd (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ ips_read_request (struct bio*) ; 
 int /*<<< orphan*/  ipsd_finish (struct bio*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void ips_io_request_callback(void *cmdptr, bus_dma_segment_t *segments,int segnum, int error)
{
	ips_softc_t *sc;
	ips_command_t *command = cmdptr;
	ips_sg_element_t *sg_list;
	ips_io_cmd *command_struct;
	struct bio *iobuf = command->arg;
	int i, length = 0;
	u_int8_t cmdtype;

	sc = command->sc;
	if(error){
		printf("ips: error = %d in ips_sg_request_callback\n", error);
		bus_dmamap_unload(command->data_dmatag, command->data_dmamap);
		iobuf->bio_flags |= BIO_ERROR;
		iobuf->bio_error = ENOMEM;
		ips_insert_free_cmd(sc, command);
		ipsd_finish(iobuf);
		return;
	}
	command_struct = (ips_io_cmd *)command->command_buffer;
	command_struct->id = command->id;
	command_struct->drivenum = (uintptr_t)iobuf->bio_driver1;
	if(segnum != 1){
		if(ips_read_request(iobuf))
			cmdtype = IPS_SG_READ_CMD;
		else
			cmdtype = IPS_SG_WRITE_CMD;
		command_struct->segnum = segnum;
		sg_list = (ips_sg_element_t *)((u_int8_t *)
			   command->command_buffer + IPS_COMMAND_LEN);
		for(i = 0; i < segnum; i++){
			sg_list[i].addr = segments[i].ds_addr;
			sg_list[i].len = segments[i].ds_len;
			length += segments[i].ds_len;
		}
		command_struct->buffaddr = 
	    	    (u_int32_t)command->command_phys_addr + IPS_COMMAND_LEN;
	} else {
		if(ips_read_request(iobuf))
			cmdtype = IPS_READ_CMD;
		else
			cmdtype = IPS_WRITE_CMD;
		command_struct->buffaddr = segments[0].ds_addr;
		length = segments[0].ds_len;
	}
	command_struct->command = cmdtype;
	command_struct->lba = iobuf->bio_pblkno;
	length = (length + IPS_BLKSIZE - 1)/IPS_BLKSIZE;
	command_struct->length = length;
	bus_dmamap_sync(sc->command_dmatag, command->command_dmamap, 
			BUS_DMASYNC_PREWRITE);
	if(ips_read_request(iobuf)) {
		bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
				BUS_DMASYNC_PREREAD);
	} else {
		bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
				BUS_DMASYNC_PREWRITE);
	}
	PRINTF(10, "ips test: command id: %d segments: %d "
		"pblkno: %lld length: %d, ds_len: %d\n", command->id, segnum,
		iobuf->bio_pblkno,
		length, segments[0].ds_len);

	sc->ips_issue_cmd(command);
	return;
}