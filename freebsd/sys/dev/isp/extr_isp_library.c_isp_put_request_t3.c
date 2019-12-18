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
struct TYPE_6__ {TYPE_1__* req_dataseg; int /*<<< orphan*/  req_totalcnt; int /*<<< orphan*/ * req_cdb; int /*<<< orphan*/  req_seg_count; int /*<<< orphan*/  req_time; int /*<<< orphan*/  req_reserved; int /*<<< orphan*/  req_crn; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  req_scclun; int /*<<< orphan*/  req_target; int /*<<< orphan*/  req_lun_trn; int /*<<< orphan*/  req_handle; int /*<<< orphan*/  req_header; } ;
typedef  TYPE_2__ ispreqt3_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_count; int /*<<< orphan*/  ds_basehi; int /*<<< orphan*/  ds_base; } ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ISP_RQDSEG_T3 ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_request_t3(ispsoftc_t *isp, ispreqt3_t *src, ispreqt3_t *dst)
{
	int i;
	isp_put_hdr(isp, &src->req_header, &dst->req_header);
	ISP_IOXPUT_32(isp, src->req_handle, &dst->req_handle);
	ISP_IOXPUT_8(isp, src->req_lun_trn, &dst->req_lun_trn);
	ISP_IOXPUT_8(isp, src->req_target, &dst->req_target);
	ISP_IOXPUT_16(isp, src->req_scclun, &dst->req_scclun);
	ISP_IOXPUT_16(isp, src->req_flags,  &dst->req_flags);
	ISP_IOXPUT_8(isp, src->req_crn, &dst->req_crn);
	ISP_IOXPUT_8(isp, src->req_reserved, &dst->req_reserved);
	ISP_IOXPUT_16(isp, src->req_time, &dst->req_time);
	ISP_IOXPUT_16(isp, src->req_seg_count, &dst->req_seg_count);
	for (i = 0; i < ASIZE(src->req_cdb); i++) {
		ISP_IOXPUT_8(isp, src->req_cdb[i], &dst->req_cdb[i]);
	}
	ISP_IOXPUT_32(isp, src->req_totalcnt, &dst->req_totalcnt);
	for (i = 0; i < ISP_RQDSEG_T3; i++) {
		ISP_IOXPUT_32(isp, src->req_dataseg[i].ds_base, &dst->req_dataseg[i].ds_base);
		ISP_IOXPUT_32(isp, src->req_dataseg[i].ds_basehi, &dst->req_dataseg[i].ds_basehi);
		ISP_IOXPUT_32(isp, src->req_dataseg[i].ds_count, &dst->req_dataseg[i].ds_count);
	}
}