#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_iw_ep {TYPE_1__* qp; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_4__ {struct ib_qp* qp; } ;
struct ib_event {int event; TYPE_2__ element; int /*<<< orphan*/  device; } ;
struct ecore_iwarp_cm_event_params {int /*<<< orphan*/  event; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;
struct TYPE_3__ {struct ib_qp ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  (*) (struct ib_event*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

void
qlnxr_iw_qp_event(void *context,
	struct ecore_iwarp_cm_event_params *params,
	enum ib_event_type ib_event,
	char *str)
{
        struct qlnxr_iw_ep *ep = (struct qlnxr_iw_ep *)context;
        struct qlnxr_dev *dev = ep->dev;
        struct ib_qp *ibqp = &(ep->qp->ibqp);
        struct ib_event event;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha,
		"[context, event, event_handler] = [%p, 0x%x, %s, %p] enter\n",
		context, params->event, str, ibqp->event_handler);

        if (ibqp->event_handler) {
                event.event = ib_event;
                event.device = ibqp->device;
                event.element.qp = ibqp;
                ibqp->event_handler(&event, ibqp->qp_context);
        }

	return;
}