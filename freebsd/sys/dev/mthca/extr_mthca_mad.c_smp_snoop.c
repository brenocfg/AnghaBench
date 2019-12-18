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
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct ib_smp {scalar_t__ data; } ;
struct ib_port_info {int neighbormtu_mastersmsl; int clientrereg_resv_subnetto; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; } ;
struct TYPE_3__ {scalar_t__ mgmt_class; scalar_t__ method; scalar_t__ attr_id; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct TYPE_4__ {void* port_num; } ;
struct ib_event {TYPE_2__ element; int /*<<< orphan*/  event; struct ib_device* device; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_CLIENT_REREGISTER ; 
 int /*<<< orphan*/  IB_EVENT_LID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PKEY_CHANGE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 
 scalar_t__ IB_MGMT_METHOD_SET ; 
 scalar_t__ IB_SMP_ATTR_PKEY_TABLE ; 
 scalar_t__ IB_SMP_ATTR_PORT_INFO ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  mthca_update_rate (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 
 int /*<<< orphan*/  update_sm_ah (int /*<<< orphan*/ ,void*,scalar_t__,int) ; 

__attribute__((used)) static void smp_snoop(struct ib_device *ibdev,
		      u8 port_num,
		      const struct ib_mad *mad,
		      u16 prev_lid)
{
	struct ib_event event;

	if ((mad->mad_hdr.mgmt_class  == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     mad->mad_hdr.mgmt_class  == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) &&
	    mad->mad_hdr.method     == IB_MGMT_METHOD_SET) {
		if (mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO) {
			struct ib_port_info *pinfo =
				(struct ib_port_info *) ((struct ib_smp *) mad)->data;
			u16 lid = be16_to_cpu(pinfo->lid);

			mthca_update_rate(to_mdev(ibdev), port_num);
			update_sm_ah(to_mdev(ibdev), port_num,
				     be16_to_cpu(pinfo->sm_lid),
				     pinfo->neighbormtu_mastersmsl & 0xf);

			event.device           = ibdev;
			event.element.port_num = port_num;

			if (pinfo->clientrereg_resv_subnetto & 0x80) {
				event.event    = IB_EVENT_CLIENT_REREGISTER;
				ib_dispatch_event(&event);
			}

			if (prev_lid != lid) {
				event.event    = IB_EVENT_LID_CHANGE;
				ib_dispatch_event(&event);
			}
		}

		if (mad->mad_hdr.attr_id == IB_SMP_ATTR_PKEY_TABLE) {
			event.device           = ibdev;
			event.event            = IB_EVENT_PKEY_CHANGE;
			event.element.port_num = port_num;
			ib_dispatch_event(&event);
		}
	}
}