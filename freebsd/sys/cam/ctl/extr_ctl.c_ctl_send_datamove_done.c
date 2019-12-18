#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  num_dmas; int /*<<< orphan*/  dma_bt; int /*<<< orphan*/  dma_start_bt; int /*<<< orphan*/  port_status; int /*<<< orphan*/  status; int /*<<< orphan*/  nexus; int /*<<< orphan*/  remote_io; } ;
struct TYPE_6__ {scalar_t__ sense_len; int /*<<< orphan*/  sense_data; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  tag_type; int /*<<< orphan*/  tag_num; int /*<<< orphan*/  kern_data_resid; } ;
union ctl_io {TYPE_4__ io_hdr; TYPE_2__ scsiio; } ;
struct TYPE_7__ {scalar_t__ sense_len; int /*<<< orphan*/  port_status; int /*<<< orphan*/  sense_data; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  tag_type; int /*<<< orphan*/  tag_num; int /*<<< orphan*/  kern_data_resid; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  nexus; int /*<<< orphan*/  serializing_sc; union ctl_io* original_sc; int /*<<< orphan*/  msg_type; } ;
union ctl_ha_msg {TYPE_3__ scsi; TYPE_1__ hdr; } ;
struct bintime {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int CTL_FLAG_FAILOVER ; 
 int CTL_FLAG_IO_ACTIVE ; 
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 int /*<<< orphan*/  CTL_MSG_DATAMOVE_DONE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bintime_add (int /*<<< orphan*/ *,struct bintime*) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_failover_io (union ctl_io*,int) ; 
 int /*<<< orphan*/  ctl_ha_msg_send (int /*<<< orphan*/ ,union ctl_ha_msg*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbinuptime (struct bintime*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (union ctl_ha_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ctl_send_datamove_done(union ctl_io *io, int have_lock)
{
	union ctl_ha_msg msg;
#ifdef CTL_TIME_IO
	struct bintime cur_bt;
#endif

	memset(&msg, 0, sizeof(msg));
	msg.hdr.msg_type = CTL_MSG_DATAMOVE_DONE;
	msg.hdr.original_sc = io;
	msg.hdr.serializing_sc = io->io_hdr.remote_io;
	msg.hdr.nexus = io->io_hdr.nexus;
	msg.hdr.status = io->io_hdr.status;
	msg.scsi.kern_data_resid = io->scsiio.kern_data_resid;
	msg.scsi.tag_num = io->scsiio.tag_num;
	msg.scsi.tag_type = io->scsiio.tag_type;
	msg.scsi.scsi_status = io->scsiio.scsi_status;
	memcpy(&msg.scsi.sense_data, &io->scsiio.sense_data,
	       io->scsiio.sense_len);
	msg.scsi.sense_len = io->scsiio.sense_len;
	msg.scsi.port_status = io->io_hdr.port_status;
	io->io_hdr.flags &= ~CTL_FLAG_IO_ACTIVE;
	if (io->io_hdr.flags & CTL_FLAG_FAILOVER) {
		ctl_failover_io(io, /*have_lock*/ have_lock);
		return;
	}
	ctl_ha_msg_send(CTL_HA_CHAN_CTL, &msg,
	    sizeof(msg.scsi) - sizeof(msg.scsi.sense_data) +
	    msg.scsi.sense_len, M_WAITOK);

#ifdef CTL_TIME_IO
	getbinuptime(&cur_bt);
	bintime_sub(&cur_bt, &io->io_hdr.dma_start_bt);
	bintime_add(&io->io_hdr.dma_bt, &cur_bt);
#endif
	io->io_hdr.num_dmas++;
}