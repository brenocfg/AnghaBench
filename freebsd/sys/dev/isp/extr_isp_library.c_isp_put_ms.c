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
struct TYPE_6__ {TYPE_1__* ms_dataseg; int /*<<< orphan*/  ms_cmd_bcnt; int /*<<< orphan*/  ms_rsp_bcnt; int /*<<< orphan*/  ms_reserved2; int /*<<< orphan*/  ms_rxid; int /*<<< orphan*/  ms_r_ctl; int /*<<< orphan*/  ms_type; int /*<<< orphan*/  ms_tot_cnt; int /*<<< orphan*/  ms_cmd_cnt; int /*<<< orphan*/  ms_time; int /*<<< orphan*/  ms_reserved1; int /*<<< orphan*/  ms_flags; int /*<<< orphan*/  ms_status; int /*<<< orphan*/  ms_nphdl; int /*<<< orphan*/  ms_handle; int /*<<< orphan*/  ms_header; } ;
typedef  TYPE_2__ isp_ms_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_count; int /*<<< orphan*/  ds_basehi; int /*<<< orphan*/  ds_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_ms(ispsoftc_t *isp, isp_ms_t *src, isp_ms_t *dst)
{
	int i;

	isp_put_hdr(isp, &src->ms_header, &dst->ms_header);
	ISP_IOXPUT_32(isp, src->ms_handle, &dst->ms_handle);
	ISP_IOXPUT_16(isp, src->ms_nphdl, &dst->ms_nphdl);
	ISP_IOXPUT_16(isp, src->ms_status, &dst->ms_status);
	ISP_IOXPUT_16(isp, src->ms_flags, &dst->ms_flags);
	ISP_IOXPUT_16(isp, src->ms_reserved1, &dst->ms_reserved1);
	ISP_IOXPUT_16(isp, src->ms_time, &dst->ms_time);
	ISP_IOXPUT_16(isp, src->ms_cmd_cnt, &dst->ms_cmd_cnt);
	ISP_IOXPUT_16(isp, src->ms_tot_cnt, &dst->ms_tot_cnt);
	ISP_IOXPUT_8(isp, src->ms_type, &dst->ms_type);
	ISP_IOXPUT_8(isp, src->ms_r_ctl, &dst->ms_r_ctl);
	ISP_IOXPUT_16(isp, src->ms_rxid, &dst->ms_rxid);
	ISP_IOXPUT_16(isp, src->ms_reserved2, &dst->ms_reserved2);
	ISP_IOXPUT_32(isp, src->ms_rsp_bcnt, &dst->ms_rsp_bcnt);
	ISP_IOXPUT_32(isp, src->ms_cmd_bcnt, &dst->ms_cmd_bcnt);
	for (i = 0; i < 2; i++) {
		ISP_IOXPUT_32(isp, src->ms_dataseg[i].ds_base, &dst->ms_dataseg[i].ds_base);
		ISP_IOXPUT_32(isp, src->ms_dataseg[i].ds_basehi, &dst->ms_dataseg[i].ds_basehi);
		ISP_IOXPUT_32(isp, src->ms_dataseg[i].ds_count, &dst->ms_dataseg[i].ds_count);
	}
}