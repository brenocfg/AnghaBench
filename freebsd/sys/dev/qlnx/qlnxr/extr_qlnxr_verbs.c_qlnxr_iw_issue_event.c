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
struct qlnxr_iw_ep {TYPE_2__* cm_id; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct iw_cm_event {int event; int /*<<< orphan*/  status; int /*<<< orphan*/  private_data_len; void* private_data; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; } ;
struct ecore_iwarp_cm_event_params {TYPE_1__* cm_info; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  int /*<<< orphan*/  event ;
typedef  enum iw_cm_event_type { ____Placeholder_iw_cm_event_type } iw_cm_event_type ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (TYPE_2__*,struct iw_cm_event*) ;} ;
struct TYPE_3__ {scalar_t__ private_data; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct iw_cm_event*) ; 

__attribute__((used)) static void
qlnxr_iw_issue_event(void *context,
	 struct ecore_iwarp_cm_event_params *params,
	 enum iw_cm_event_type event_type,
	 char *str)
{
	struct qlnxr_iw_ep *ep = (struct qlnxr_iw_ep *)context;
	struct qlnxr_dev *dev = ep->dev;
	struct iw_cm_event event;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	memset(&event, 0, sizeof(event));
	event.status = params->status;
	event.event = event_type;

	if (params->cm_info != NULL) {
#if __FreeBSD_version >= 1100000
		event.ird = params->cm_info->ird;
		event.ord = params->cm_info->ord;
		QL_DPRINT12(ha, "ord=[%d] \n", event.ord);
		QL_DPRINT12(ha, "ird=[%d] \n", event.ird);
#endif /* #if __FreeBSD_version >= 1100000 */

		event.private_data_len = params->cm_info->private_data_len;
		event.private_data = (void *)params->cm_info->private_data;
		QL_DPRINT12(ha, "private_data_len=[%d] \n",
			event.private_data_len);
	}

	QL_DPRINT12(ha, "event=[%d] %s\n", event.event, str);
	QL_DPRINT12(ha, "status=[%d] \n", event.status);
	
	if (ep) {
		if (ep->cm_id)
			ep->cm_id->event_handler(ep->cm_id, &event);
		else
			QL_DPRINT11(ha, "ep->cm_id == NULL \n");
	} else {
		QL_DPRINT11(ha, "ep == NULL \n");
	}

	QL_DPRINT12(ha, "exit\n");

	return;
}