#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sense_data; } ;
struct vmscsi_req {int scsi_status; int srb_status; scalar_t__ sense_info_len; TYPE_5__ u; int /*<<< orphan*/  transfer_len; } ;
struct TYPE_6__ {struct vmscsi_req vm_srb; } ;
struct vstor_packet {TYPE_1__ u; } ;
struct storvsc_softc {scalar_t__ hs_num_out_reqs; int /*<<< orphan*/  hs_drain_sema; scalar_t__ hs_drain_notify; } ;
struct TYPE_7__ {int scsi_status; int srb_status; int /*<<< orphan*/  transfer_len; } ;
struct TYPE_8__ {TYPE_2__ vm_srb; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct hv_storvsc_request {scalar_t__ sense_info_len; int /*<<< orphan*/  sense_data; TYPE_4__ vstor_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SCSI_STATUS_CHECK_COND ; 
 int SRB_STATUS_AUTOSENSE_VALID ; 
 int /*<<< orphan*/  atomic_subtract_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sema_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storvsc_io_done (struct hv_storvsc_request*) ; 

__attribute__((used)) static void
hv_storvsc_on_iocompletion(struct storvsc_softc *sc,
			   struct vstor_packet *vstor_packet,
			   struct hv_storvsc_request *request)
{
	struct vmscsi_req *vm_srb;

	vm_srb = &vstor_packet->u.vm_srb;

	/*
	 * Copy some fields of the host's response into the request structure,
	 * because the fields will be used later in storvsc_io_done().
	 */
	request->vstor_packet.u.vm_srb.scsi_status = vm_srb->scsi_status;
	request->vstor_packet.u.vm_srb.srb_status = vm_srb->srb_status;
	request->vstor_packet.u.vm_srb.transfer_len = vm_srb->transfer_len;

	if (((vm_srb->scsi_status & 0xFF) == SCSI_STATUS_CHECK_COND) &&
			(vm_srb->srb_status & SRB_STATUS_AUTOSENSE_VALID)) {
		/* Autosense data available */

		KASSERT(vm_srb->sense_info_len <= request->sense_info_len,
				("vm_srb->sense_info_len <= "
				 "request->sense_info_len"));

		memcpy(request->sense_data, vm_srb->u.sense_data,
			vm_srb->sense_info_len);

		request->sense_info_len = vm_srb->sense_info_len;
	}

	/* Complete request by passing to the CAM layer */
	storvsc_io_done(request);
	atomic_subtract_int(&sc->hs_num_out_reqs, 1);
	if (sc->hs_drain_notify && (sc->hs_num_out_reqs == 0)) {
		sema_post(&sc->hs_drain_sema);
	}
}