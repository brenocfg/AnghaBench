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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_count; int /*<<< orphan*/  ds_basehi; int /*<<< orphan*/  ds_base; } ;
struct TYPE_6__ {TYPE_1__ req_dataseg; int /*<<< orphan*/  req_vpidx; int /*<<< orphan*/  req_tidhi; int /*<<< orphan*/  req_tidlo; int /*<<< orphan*/  req_dl; scalar_t__ req_cdb; int /*<<< orphan*/  req_crn; int /*<<< orphan*/  req_task_attribute; int /*<<< orphan*/  req_task_management; int /*<<< orphan*/  req_alen_datadir; scalar_t__ req_lun; int /*<<< orphan*/  req_reserved; int /*<<< orphan*/  req_seg_count; int /*<<< orphan*/  req_time; int /*<<< orphan*/  req_nphdl; int /*<<< orphan*/  req_handle; int /*<<< orphan*/  req_header; } ;
typedef  TYPE_2__ ispreqt7_t ;

/* Variables and functions */
 int ASIZE (scalar_t__) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ISP_SWAP32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_request_t7(ispsoftc_t *isp, ispreqt7_t *src, ispreqt7_t *dst)
{
	int i;
	uint32_t *a, *b;

	isp_put_hdr(isp, &src->req_header, &dst->req_header);
	ISP_IOXPUT_32(isp, src->req_handle, &dst->req_handle);
	ISP_IOXPUT_16(isp, src->req_nphdl, &dst->req_nphdl);
	ISP_IOXPUT_16(isp, src->req_time, &dst->req_time);
	ISP_IOXPUT_16(isp, src->req_seg_count, &dst->req_seg_count);
	ISP_IOXPUT_16(isp, src->req_reserved, &dst->req_reserved);
	a = (uint32_t *) src->req_lun;
	b = (uint32_t *) dst->req_lun;
	for (i = 0; i < (ASIZE(src->req_lun) >> 2); i++ ) {
		*b++ = ISP_SWAP32(isp, *a++);
	}
	ISP_IOXPUT_8(isp, src->req_alen_datadir, &dst->req_alen_datadir);
	ISP_IOXPUT_8(isp, src->req_task_management, &dst->req_task_management);
	ISP_IOXPUT_8(isp, src->req_task_attribute, &dst->req_task_attribute);
	ISP_IOXPUT_8(isp, src->req_crn, &dst->req_crn);
	a = (uint32_t *) src->req_cdb;
	b = (uint32_t *) dst->req_cdb;
	for (i = 0; i < (ASIZE(src->req_cdb) >> 2); i++) {
		*b++ = ISP_SWAP32(isp, *a++);
	}
	ISP_IOXPUT_32(isp, src->req_dl, &dst->req_dl);
	ISP_IOXPUT_16(isp, src->req_tidlo, &dst->req_tidlo);
	ISP_IOXPUT_8(isp, src->req_tidhi, &dst->req_tidhi);
	ISP_IOXPUT_8(isp, src->req_vpidx, &dst->req_vpidx);
	ISP_IOXPUT_32(isp, src->req_dataseg.ds_base, &dst->req_dataseg.ds_base);
	ISP_IOXPUT_32(isp, src->req_dataseg.ds_basehi, &dst->req_dataseg.ds_basehi);
	ISP_IOXPUT_32(isp, src->req_dataseg.ds_count, &dst->req_dataseg.ds_count);
}