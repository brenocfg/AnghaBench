#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int lun; scalar_t__ transfer_len; int /*<<< orphan*/  sense_info_len; scalar_t__ length; } ;
struct TYPE_8__ {TYPE_1__ vm_srb; } ;
struct vstor_packet {TYPE_2__ u; int /*<<< orphan*/  operation; int /*<<< orphan*/  flags; } ;
struct vmscsi_req {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * chan_send_cnt; } ;
struct storvsc_softc {int hs_nchan; int /*<<< orphan*/  hs_num_out_reqs; TYPE_4__ sysctl_data; struct vmbus_channel** hs_sel_chan; } ;
struct TYPE_12__ {scalar_t__ gpa_len; } ;
struct TYPE_9__ {TYPE_6__ gpa_range; } ;
struct hv_storvsc_request {TYPE_5__* softc; int /*<<< orphan*/  prp_cnt; TYPE_3__ prp_list; struct vstor_packet vstor_packet; } ;
struct TYPE_11__ {int /*<<< orphan*/  hs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_COMPLETION_FLAG ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_FLAG_RC ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_TYPE_INBAND ; 
 int /*<<< orphan*/  VSTOR_OPERATION_EXECUTESRB ; 
 int /*<<< orphan*/  VSTOR_PKT_SIZE ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int curcpu ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,struct vstor_packet*,int) ; 
 int /*<<< orphan*/  sense_buffer_size ; 
 int vmbus_chan_send (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vstor_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmbus_chan_send_prplist (struct vmbus_channel*,TYPE_6__*,int /*<<< orphan*/ ,struct vstor_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmscsi_size_delta ; 

__attribute__((used)) static int
hv_storvsc_io_request(struct storvsc_softc *sc,
					  struct hv_storvsc_request *request)
{
	struct vstor_packet *vstor_packet = &request->vstor_packet;
	struct vmbus_channel* outgoing_channel = NULL;
	int ret = 0, ch_sel;

	vstor_packet->flags |= REQUEST_COMPLETION_FLAG;

	vstor_packet->u.vm_srb.length =
	    sizeof(struct vmscsi_req) - vmscsi_size_delta;
	
	vstor_packet->u.vm_srb.sense_info_len = sense_buffer_size;

	vstor_packet->u.vm_srb.transfer_len =
	    request->prp_list.gpa_range.gpa_len;

	vstor_packet->operation = VSTOR_OPERATION_EXECUTESRB;

	ch_sel = (vstor_packet->u.vm_srb.lun + curcpu) % sc->hs_nchan;
	outgoing_channel = sc->hs_sel_chan[ch_sel];

	mtx_unlock(&request->softc->hs_lock);
	if (request->prp_list.gpa_range.gpa_len) {
		ret = vmbus_chan_send_prplist(outgoing_channel,
		    &request->prp_list.gpa_range, request->prp_cnt,
		    vstor_packet, VSTOR_PKT_SIZE, (uint64_t)(uintptr_t)request);
	} else {
		ret = vmbus_chan_send(outgoing_channel,
		    VMBUS_CHANPKT_TYPE_INBAND, VMBUS_CHANPKT_FLAG_RC,
		    vstor_packet, VSTOR_PKT_SIZE, (uint64_t)(uintptr_t)request);
	}
	/* statistic for successful request sending on each channel */
	if (!ret) {
		sc->sysctl_data.chan_send_cnt[ch_sel]++;
	}
	mtx_lock(&request->softc->hs_lock);

	if (ret != 0) {
		printf("Unable to send packet %p ret %d", vstor_packet, ret);
	} else {
		atomic_add_int(&sc->hs_num_out_reqs, 1);
	}

	return (ret);
}