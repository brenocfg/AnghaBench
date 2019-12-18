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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_4__ {scalar_t__ req_rsp_sense; int /*<<< orphan*/  req_response_len; int /*<<< orphan*/  req_sense_len; int /*<<< orphan*/  req_fcp_residual; int /*<<< orphan*/  req_scsi_status; int /*<<< orphan*/  req_retry_delay; int /*<<< orphan*/  req_state_flags; int /*<<< orphan*/  req_reserved0; int /*<<< orphan*/  req_resid; int /*<<< orphan*/  req_oxid; int /*<<< orphan*/  req_completion_status; int /*<<< orphan*/  req_handle; int /*<<< orphan*/  req_header; } ;
typedef  TYPE_1__ isp24xx_statusreq_t ;

/* Variables and functions */
 int ASIZE (scalar_t__) ; 
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_SWAP32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_get_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_get_24xx_response(ispsoftc_t *isp, isp24xx_statusreq_t *src, isp24xx_statusreq_t *dst)
{
	int i;
	uint32_t *s, *d;

	isp_get_hdr(isp, &src->req_header, &dst->req_header);
	ISP_IOXGET_32(isp, &src->req_handle, dst->req_handle);
	ISP_IOXGET_16(isp, &src->req_completion_status, dst->req_completion_status);
	ISP_IOXGET_16(isp, &src->req_oxid, dst->req_oxid);
	ISP_IOXGET_32(isp, &src->req_resid, dst->req_resid);
	ISP_IOXGET_16(isp, &src->req_reserved0, dst->req_reserved0);
	ISP_IOXGET_16(isp, &src->req_state_flags, dst->req_state_flags);
	ISP_IOXGET_16(isp, &src->req_retry_delay, dst->req_retry_delay);
	ISP_IOXGET_16(isp, &src->req_scsi_status, dst->req_scsi_status);
	ISP_IOXGET_32(isp, &src->req_fcp_residual, dst->req_fcp_residual);
	ISP_IOXGET_32(isp, &src->req_sense_len, dst->req_sense_len);
	ISP_IOXGET_32(isp, &src->req_response_len, dst->req_response_len);
	s = (uint32_t *)src->req_rsp_sense;
	d = (uint32_t *)dst->req_rsp_sense;
	for (i = 0; i < (ASIZE(src->req_rsp_sense) >> 2); i++) {
		d[i] = ISP_SWAP32(isp, s[i]);
	}
}