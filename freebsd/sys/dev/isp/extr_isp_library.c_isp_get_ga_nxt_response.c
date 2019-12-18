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
struct TYPE_4__ {int /*<<< orphan*/ * snscb_hardaddr; int /*<<< orphan*/  snscb_reserved; int /*<<< orphan*/ * snscb_fpname; int /*<<< orphan*/ * snscb_fc4_types; int /*<<< orphan*/ * snscb_svc_class; int /*<<< orphan*/ * snscb_ipaddr; int /*<<< orphan*/ * snscb_ipassoc; int /*<<< orphan*/ * snscb_nname; int /*<<< orphan*/  snscb_nnlen; int /*<<< orphan*/ * snscb_nodename; int /*<<< orphan*/ * snscb_pname; int /*<<< orphan*/  snscb_pnlen; int /*<<< orphan*/ * snscb_portname; int /*<<< orphan*/ * snscb_port_id; int /*<<< orphan*/  snscb_port_type; int /*<<< orphan*/  snscb_cthdr; } ;
typedef  TYPE_1__ sns_ga_nxt_rsp_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_get_ct_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_get_ga_nxt_response(ispsoftc_t *isp, sns_ga_nxt_rsp_t *src, sns_ga_nxt_rsp_t *dst)
{
	int i;
	isp_get_ct_hdr(isp, &src->snscb_cthdr, &dst->snscb_cthdr);
	ISP_IOZGET_8(isp, &src->snscb_port_type, dst->snscb_port_type);
	for (i = 0; i < 3; i++) {
		ISP_IOZGET_8(isp, &src->snscb_port_id[i], dst->snscb_port_id[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOZGET_8(isp, &src->snscb_portname[i], dst->snscb_portname[i]);
	}
	ISP_IOZGET_8(isp, &src->snscb_pnlen, dst->snscb_pnlen);
	for (i = 0; i < 255; i++) {
		ISP_IOZGET_8(isp, &src->snscb_pname[i], dst->snscb_pname[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOZGET_8(isp, &src->snscb_nodename[i], dst->snscb_nodename[i]);
	}
	ISP_IOZGET_8(isp, &src->snscb_nnlen, dst->snscb_nnlen);
	for (i = 0; i < 255; i++) {
		ISP_IOZGET_8(isp, &src->snscb_nname[i], dst->snscb_nname[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOZGET_8(isp, &src->snscb_ipassoc[i], dst->snscb_ipassoc[i]);
	}
	for (i = 0; i < 16; i++) {
		ISP_IOZGET_8(isp, &src->snscb_ipaddr[i], dst->snscb_ipaddr[i]);
	}
	for (i = 0; i < 4; i++) {
		ISP_IOZGET_8(isp, &src->snscb_svc_class[i], dst->snscb_svc_class[i]);
	}
	for (i = 0; i < 32; i++) {
		ISP_IOZGET_8(isp, &src->snscb_fc4_types[i], dst->snscb_fc4_types[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOZGET_8(isp, &src->snscb_fpname[i], dst->snscb_fpname[i]);
	}
	ISP_IOZGET_8(isp, &src->snscb_reserved, dst->snscb_reserved);
	for (i = 0; i < 3; i++) {
		ISP_IOZGET_8(isp, &src->snscb_hardaddr[i], dst->snscb_hardaddr[i]);
	}
}