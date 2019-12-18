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
struct TYPE_4__ {int /*<<< orphan*/  fcp_rsp_rsplen; int /*<<< orphan*/  fcp_rsp_snslen; int /*<<< orphan*/  fcp_rsp_resid; int /*<<< orphan*/  fcp_rsp_scsi_status; int /*<<< orphan*/  fcp_rsp_bits; int /*<<< orphan*/  fcp_rsp_status_qualifier; int /*<<< orphan*/ * fcp_rsp_reserved; } ;
typedef  TYPE_1__ fcp_rsp_iu_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOZPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOZPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isp_put_fcp_rsp_iu(ispsoftc_t *isp, fcp_rsp_iu_t *src, fcp_rsp_iu_t *dst)
{
	int i;
	for (i = 0; i < ((sizeof (src->fcp_rsp_reserved))/(sizeof (src->fcp_rsp_reserved[0]))); i++) {
		ISP_IOZPUT_8(isp, src->fcp_rsp_reserved[i], &dst->fcp_rsp_reserved[i]);
	}
	ISP_IOZPUT_16(isp, src->fcp_rsp_status_qualifier, &dst->fcp_rsp_status_qualifier);
	ISP_IOZPUT_8(isp, src->fcp_rsp_bits, &dst->fcp_rsp_bits);
	ISP_IOZPUT_8(isp, src->fcp_rsp_scsi_status, &dst->fcp_rsp_scsi_status);
	ISP_IOZPUT_32(isp, src->fcp_rsp_resid, &dst->fcp_rsp_resid);
	ISP_IOZPUT_32(isp, src->fcp_rsp_snslen, &dst->fcp_rsp_snslen);
	ISP_IOZPUT_32(isp, src->fcp_rsp_rsplen, &dst->fcp_rsp_rsplen);
}