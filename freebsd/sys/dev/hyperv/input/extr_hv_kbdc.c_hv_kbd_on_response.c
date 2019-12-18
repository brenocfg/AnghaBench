#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vmbus_xact_ctx {int dummy; } ;
struct vmbus_chanpkt_hdr {int dummy; } ;
struct TYPE_4__ {struct vmbus_xact_ctx* hs_xact_ctx; } ;
typedef  TYPE_1__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_CONST_DATA (struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_DATALEN (struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  vmbus_xact_ctx_wakeup (struct vmbus_xact_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hv_kbd_on_response(hv_kbd_sc *sc, struct vmbus_chanpkt_hdr *pkt)
{
	struct vmbus_xact_ctx *xact = sc->hs_xact_ctx;
	if (xact != NULL) {
		DEBUG_HVSC(sc, "hvkbd is ready\n");
		vmbus_xact_ctx_wakeup(xact, VMBUS_CHANPKT_CONST_DATA(pkt),
		    VMBUS_CHANPKT_DATALEN(pkt));
	}
}