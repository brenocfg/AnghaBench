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
struct TYPE_4__ {int /*<<< orphan*/  vp_port_portid_hi; int /*<<< orphan*/  vp_port_portid_lo; int /*<<< orphan*/ * vp_port_nodename; int /*<<< orphan*/ * vp_port_portname; int /*<<< orphan*/  vp_port_loopid; int /*<<< orphan*/  vp_port_options; int /*<<< orphan*/  vp_port_status; } ;
typedef  TYPE_1__ vp_port_info_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isp_get_vp_port_info(ispsoftc_t *isp, vp_port_info_t *src, vp_port_info_t *dst)
{
	int i;
	ISP_IOXGET_16(isp, &src->vp_port_status, dst->vp_port_status);
	ISP_IOXGET_8(isp, &src->vp_port_options, dst->vp_port_options);
	ISP_IOXGET_8(isp, &src->vp_port_loopid, dst->vp_port_loopid);
	for (i = 0; i < ASIZE(src->vp_port_portname); i++) {
		ISP_IOXGET_8(isp, &src->vp_port_portname[i], dst->vp_port_portname[i]);
	}
	for (i = 0; i < ASIZE(src->vp_port_nodename); i++) {
		ISP_IOXGET_8(isp, &src->vp_port_nodename[i], dst->vp_port_nodename[i]);
	}
	ISP_IOXGET_16(isp, &src->vp_port_portid_lo, dst->vp_port_portid_lo);
	ISP_IOXGET_16(isp, &src->vp_port_portid_hi, dst->vp_port_portid_hi);
}