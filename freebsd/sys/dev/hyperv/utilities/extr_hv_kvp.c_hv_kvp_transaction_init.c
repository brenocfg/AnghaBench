#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct hv_vmbus_pipe_hdr {int dummy; } ;
struct hv_vmbus_icmsg_hdr {int dummy; } ;
struct hv_kvp_msg {int dummy; } ;
struct TYPE_3__ {int req_in_progress; struct hv_kvp_msg* host_kvp_msg; int /*<<< orphan*/ * rcv_buf; int /*<<< orphan*/  host_msg_id; int /*<<< orphan*/  host_msg_len; } ;
typedef  TYPE_1__ hv_kvp_sc ;

/* Variables and functions */

__attribute__((used)) static void
hv_kvp_transaction_init(hv_kvp_sc *sc, uint32_t rcv_len,
			uint64_t request_id, uint8_t *rcv_buf)
{

	/* Store all the relevant message details in the global structure */
	/* Do not need to use mutex for req_in_progress here */
	sc->req_in_progress = true;
	sc->host_msg_len = rcv_len;
	sc->host_msg_id = request_id;
	sc->rcv_buf = rcv_buf;
	sc->host_kvp_msg = (struct hv_kvp_msg *)&rcv_buf[
	    sizeof(struct hv_vmbus_pipe_hdr) +
	    sizeof(struct hv_vmbus_icmsg_hdr)];
}