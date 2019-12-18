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
struct TYPE_6__ {TYPE_1__* req_dataseg; int /*<<< orphan*/ * req_cdb; int /*<<< orphan*/  req_seg_count; int /*<<< orphan*/  req_time; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  req_cdblen; int /*<<< orphan*/  req_target; int /*<<< orphan*/  req_lun_trn; int /*<<< orphan*/  req_handle; int /*<<< orphan*/  req_header; } ;
typedef  TYPE_2__ ispreq_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_count; int /*<<< orphan*/  ds_base; } ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ISP_IS_SBUS (int /*<<< orphan*/ *) ; 
 int ISP_RQDSEG ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_request(ispsoftc_t *isp, ispreq_t *rqsrc, ispreq_t *rqdst)
{
	int i;
	isp_put_hdr(isp, &rqsrc->req_header, &rqdst->req_header);
	ISP_IOXPUT_32(isp, rqsrc->req_handle, &rqdst->req_handle);
	if (ISP_IS_SBUS(isp)) {
		ISP_IOXPUT_8(isp, rqsrc->req_lun_trn, &rqdst->req_target);
		ISP_IOXPUT_8(isp, rqsrc->req_target, &rqdst->req_lun_trn);
	} else {
		ISP_IOXPUT_8(isp, rqsrc->req_lun_trn, &rqdst->req_lun_trn);
		ISP_IOXPUT_8(isp, rqsrc->req_target, &rqdst->req_target);
	}
	ISP_IOXPUT_16(isp, rqsrc->req_cdblen, &rqdst->req_cdblen);
	ISP_IOXPUT_16(isp, rqsrc->req_flags, &rqdst->req_flags);
	ISP_IOXPUT_16(isp, rqsrc->req_time, &rqdst->req_time);
	ISP_IOXPUT_16(isp, rqsrc->req_seg_count, &rqdst->req_seg_count);
	for (i = 0; i < ASIZE(rqsrc->req_cdb); i++) {
		ISP_IOXPUT_8(isp, rqsrc->req_cdb[i], &rqdst->req_cdb[i]);
	}
	for (i = 0; i < ISP_RQDSEG; i++) {
		ISP_IOXPUT_32(isp, rqsrc->req_dataseg[i].ds_base, &rqdst->req_dataseg[i].ds_base);
		ISP_IOXPUT_32(isp, rqsrc->req_dataseg[i].ds_count, &rqdst->req_dataseg[i].ds_count);
	}
}