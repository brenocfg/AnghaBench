#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ts_mad ;
struct ib_mad {int format_version; int attribute_id; int class_version; int slid; int transaction_id; int /*<<< orphan*/  dlid; int /*<<< orphan*/  dqpn; int /*<<< orphan*/  sqpn; int /*<<< orphan*/  port; int /*<<< orphan*/  r_method; int /*<<< orphan*/  mgmt_class; } ;
struct TYPE_7__ {int /*<<< orphan*/  lid; } ;
struct ib_get_port_info_ioctl {TYPE_2__ port_info; int /*<<< orphan*/  port; } ;
struct TYPE_8__ {int /*<<< orphan*/  port_num; scalar_t__ p_transp_mgr; } ;
typedef  TYPE_3__ osmv_bind_obj_t ;
struct TYPE_6__ {int /*<<< orphan*/  qpn; int /*<<< orphan*/  mgmt_class; } ;
struct TYPE_9__ {int /*<<< orphan*/  device_fd; TYPE_1__ filter; } ;
typedef  TYPE_4__ osmv_TOPSPIN_transport_mgr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_IB_IOCGPORTINFO ; 
 int /*<<< orphan*/  cl_ntoh16 (int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_get_port_info_ioctl*) ; 
 int /*<<< orphan*/  memset (struct ib_mad*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,struct ib_mad*,int) ; 

void __osm_transport_gen_dummy_mad(osmv_bind_obj_t * p_bo)
{
	struct ib_mad ts_mad;
	osmv_TOPSPIN_transport_mgr_t *p_mgr =
	    (osmv_TOPSPIN_transport_mgr_t *) (p_bo->p_transp_mgr);
	struct ib_get_port_info_ioctl port_data;
	int ts_ioctl_ret;

	/* prepare the mad fields following the stored filter on the bind */
	memset(&ts_mad, 0, sizeof(ts_mad));
	ts_mad.format_version = 1;
	ts_mad.mgmt_class = p_mgr->filter.mgmt_class;
	ts_mad.attribute_id = 0x2;
	ts_mad.class_version = 1;
	ts_mad.r_method = cl_ntoh16(0x2);
	ts_mad.port = p_bo->port_num;
	ts_mad.sqpn = p_mgr->filter.qpn;
	ts_mad.dqpn = p_mgr->filter.qpn;
	ts_mad.slid = 0xffff;
	/* we must send to our local lid ... */
	port_data.port = p_bo->port_num;
	ts_ioctl_ret = ioctl(p_mgr->device_fd, TS_IB_IOCGPORTINFO, &port_data);
	ts_mad.dlid = port_data.port_info.lid;
	ts_mad.transaction_id = 0x9999;
	write(p_mgr->device_fd, &ts_mad, sizeof(ts_mad));
}