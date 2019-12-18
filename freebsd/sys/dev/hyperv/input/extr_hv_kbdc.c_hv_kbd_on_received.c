#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vmbus_chanpkt_hdr {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ hv_kbd_sc ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ hv_kbd_proto_resp ;
struct TYPE_12__ {int type; } ;
struct TYPE_15__ {TYPE_1__ hdr; } ;
typedef  TYPE_4__ hv_kbd_msg ;
struct TYPE_17__ {int info; int /*<<< orphan*/  makecode; } ;
struct TYPE_16__ {TYPE_7__ ks; } ;
typedef  TYPE_5__ hv_kbd_keystroke ;
typedef  enum hv_kbd_msg_type_t { ____Placeholder_hv_kbd_msg_type_t } hv_kbd_msg_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_2__*,char*,int,...) ; 
#define  HV_KBD_PROTO_EVENT 129 
#define  HV_KBD_PROTO_RESPONSE 128 
 void* VMBUS_CHANPKT_CONST_DATA (struct vmbus_chanpkt_hdr*) ; 
 int VMBUS_CHANPKT_DATALEN (struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hv_kbd_intr (TYPE_2__*) ; 
 int /*<<< orphan*/  hv_kbd_on_response (TYPE_2__*,struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  hv_kbd_produce_ks (TYPE_2__*,TYPE_7__*) ; 

__attribute__((used)) static void
hv_kbd_on_received(hv_kbd_sc *sc, struct vmbus_chanpkt_hdr *pkt)
{

	const hv_kbd_msg *msg = VMBUS_CHANPKT_CONST_DATA(pkt);
	const hv_kbd_proto_resp *resp =
	    VMBUS_CHANPKT_CONST_DATA(pkt);
	const hv_kbd_keystroke *keystroke =
	    VMBUS_CHANPKT_CONST_DATA(pkt);
	uint32_t msg_len = VMBUS_CHANPKT_DATALEN(pkt);
	enum hv_kbd_msg_type_t msg_type;
	uint32_t info;
	uint16_t scan_code;

	if (msg_len <= sizeof(hv_kbd_msg)) {
		device_printf(sc->dev, "Illegal packet\n");
		return;
	}
	msg_type = msg->hdr.type;
	switch (msg_type) {
		case HV_KBD_PROTO_RESPONSE:
			hv_kbd_on_response(sc, pkt);
			DEBUG_HVSC(sc, "keyboard resp: 0x%x\n",
			    resp->status);
			break;
		case HV_KBD_PROTO_EVENT:
			info = keystroke->ks.info;
			scan_code = keystroke->ks.makecode;
			DEBUG_HVSC(sc, "keystroke info: 0x%x, scan: 0x%x\n",
			    info, scan_code);
			hv_kbd_produce_ks(sc, &keystroke->ks);
			hv_kbd_intr(sc);
		default:
			break;
	}
}