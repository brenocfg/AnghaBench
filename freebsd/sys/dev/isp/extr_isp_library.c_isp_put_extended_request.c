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
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_4__ {int /*<<< orphan*/ * req_cdb; int /*<<< orphan*/  req_seg_count; int /*<<< orphan*/  req_time; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  req_cdblen; int /*<<< orphan*/  req_target; int /*<<< orphan*/  req_lun_trn; int /*<<< orphan*/  req_handle; int /*<<< orphan*/  req_header; } ;
typedef  TYPE_1__ ispextreq_t ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ISP_IS_SBUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_extended_request(ispsoftc_t *isp, ispextreq_t *src, ispextreq_t *dst)
{
	int i;
	isp_put_hdr(isp, &src->req_header, &dst->req_header);
	ISP_IOXPUT_32(isp, src->req_handle, &dst->req_handle);
	if (ISP_IS_SBUS(isp)) {
		ISP_IOXPUT_8(isp, src->req_lun_trn, &dst->req_target);
		ISP_IOXPUT_8(isp, src->req_target, &dst->req_lun_trn);
	} else {
		ISP_IOXPUT_8(isp, src->req_lun_trn, &dst->req_lun_trn);
		ISP_IOXPUT_8(isp, src->req_target, &dst->req_target);
	}
	ISP_IOXPUT_16(isp, src->req_cdblen, &dst->req_cdblen);
	ISP_IOXPUT_16(isp, src->req_flags, &dst->req_flags);
	ISP_IOXPUT_16(isp, src->req_time, &dst->req_time);
	ISP_IOXPUT_16(isp, src->req_seg_count, &dst->req_seg_count);
	for (i = 0; i < ASIZE(src->req_cdb); i++) {
		ISP_IOXPUT_8(isp, src->req_cdb[i], &dst->req_cdb[i]);
	}
}