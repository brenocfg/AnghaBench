#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_6__ {TYPE_1__* ctp_dataseg; int /*<<< orphan*/  ctp_cmd_bcnt; int /*<<< orphan*/  ctp_rsp_bcnt; int /*<<< orphan*/ * ctp_reserved2; int /*<<< orphan*/  ctp_rsp_cnt; int /*<<< orphan*/  ctp_reserved1; int /*<<< orphan*/  ctp_time; int /*<<< orphan*/  ctp_reserved0; int /*<<< orphan*/  ctp_vpidx; int /*<<< orphan*/  ctp_cmd_cnt; int /*<<< orphan*/  ctp_nphdl; int /*<<< orphan*/  ctp_status; int /*<<< orphan*/  ctp_handle; int /*<<< orphan*/  ctp_header; } ;
typedef  TYPE_2__ isp_ct_pt_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_count; int /*<<< orphan*/  ds_basehi; int /*<<< orphan*/  ds_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_get_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_get_ct_pt(ispsoftc_t *isp, isp_ct_pt_t *src, isp_ct_pt_t *dst)
{
	int i;

	isp_get_hdr(isp, &src->ctp_header, &dst->ctp_header);
	ISP_IOXGET_32(isp, &src->ctp_handle, dst->ctp_handle);
	ISP_IOXGET_16(isp, &src->ctp_status, dst->ctp_status);
	ISP_IOXGET_16(isp, &src->ctp_nphdl, dst->ctp_nphdl);
	ISP_IOXGET_16(isp, &src->ctp_cmd_cnt, dst->ctp_cmd_cnt);
	ISP_IOXGET_8(isp, &src->ctp_vpidx, dst->ctp_vpidx);
	ISP_IOXGET_8(isp, &src->ctp_reserved0, dst->ctp_reserved0);
	ISP_IOXGET_16(isp, &src->ctp_time, dst->ctp_time);
	ISP_IOXGET_16(isp, &src->ctp_reserved1, dst->ctp_reserved1);
	ISP_IOXGET_16(isp, &src->ctp_rsp_cnt, dst->ctp_rsp_cnt);
	for (i = 0; i < 5; i++) {
		ISP_IOXGET_16(isp, &src->ctp_reserved2[i], dst->ctp_reserved2[i]);
	}
	ISP_IOXGET_32(isp, &src->ctp_rsp_bcnt, dst->ctp_rsp_bcnt);
	ISP_IOXGET_32(isp, &src->ctp_cmd_bcnt, dst->ctp_cmd_bcnt);
	for (i = 0; i < 2; i++) {
		ISP_IOXGET_32(isp, &src->ctp_dataseg[i].ds_base, dst->ctp_dataseg[i].ds_base);
		ISP_IOXGET_32(isp, &src->ctp_dataseg[i].ds_basehi, dst->ctp_dataseg[i].ds_basehi);
		ISP_IOXGET_32(isp, &src->ctp_dataseg[i].ds_count, dst->ctp_dataseg[i].ds_count);
	}
}