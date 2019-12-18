#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vmbus_xact {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  hs_chan; int /*<<< orphan*/  hs_xact_ctx; } ;
typedef  TYPE_2__ hv_kbd_sc ;
struct TYPE_12__ {int status; } ;
typedef  TYPE_3__ hv_kbd_proto_resp ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int /*<<< orphan*/  ver; TYPE_1__ hdr; } ;
typedef  TYPE_4__ hv_kbd_proto_req ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_2__*,char*) ; 
 int ENODEV ; 
 int HV_KBD_PROTO_ACCEPTED ; 
 int /*<<< orphan*/  HV_KBD_PROTO_REQUEST ; 
 size_t HV_KBD_PROTO_RESP_SZ ; 
 int /*<<< orphan*/  HV_KBD_VER ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_FLAG_RC ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_TYPE_INBAND ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int vmbus_chan_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* vmbus_chan_xact_wait (int /*<<< orphan*/ ,struct vmbus_xact*,size_t*,int) ; 
 int /*<<< orphan*/  vmbus_xact_activate (struct vmbus_xact*) ; 
 int /*<<< orphan*/  vmbus_xact_deactivate (struct vmbus_xact*) ; 
 struct vmbus_xact* vmbus_xact_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_xact_put (struct vmbus_xact*) ; 
 TYPE_4__* vmbus_xact_req_data (struct vmbus_xact*) ; 

__attribute__((used)) static int
hv_kbd_connect_vsp(hv_kbd_sc *sc)
{
	int ret;
	size_t resplen;
	struct vmbus_xact *xact;
	hv_kbd_proto_req *req;
	const hv_kbd_proto_resp *resp;

	xact = vmbus_xact_get(sc->hs_xact_ctx, sizeof(*req));
	if (xact == NULL) {
		device_printf(sc->dev, "no xact for kbd init");
		return (ENODEV);
	}
	req = vmbus_xact_req_data(xact);
	req->hdr.type = HV_KBD_PROTO_REQUEST;
	req->ver = HV_KBD_VER;

	vmbus_xact_activate(xact);
	ret = vmbus_chan_send(sc->hs_chan,
		VMBUS_CHANPKT_TYPE_INBAND,
		VMBUS_CHANPKT_FLAG_RC,
		req, sizeof(hv_kbd_proto_req),
		(uint64_t)(uintptr_t)xact);
	if (ret) {
		device_printf(sc->dev, "fail to send\n");
		vmbus_xact_deactivate(xact);
		return (ret);
	}
	resp = vmbus_chan_xact_wait(sc->hs_chan, xact, &resplen, true);
	if (resplen < HV_KBD_PROTO_RESP_SZ) {
		device_printf(sc->dev, "hv_kbd init communicate failed\n");
		ret = ENODEV;
		goto clean;
	}

	if (!(resp->status & HV_KBD_PROTO_ACCEPTED)) {
		device_printf(sc->dev, "hv_kbd protocol request failed\n");
		ret = ENODEV;
	}
clean:
	vmbus_xact_put(xact);
	DEBUG_HVSC(sc, "finish connect vsp\n");
	return (ret);
}