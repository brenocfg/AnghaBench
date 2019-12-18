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
struct TYPE_4__ {int /*<<< orphan*/  ct_vunique; int /*<<< orphan*/  ct_explanation; int /*<<< orphan*/  ct_reason; int /*<<< orphan*/  ct_reserved1; int /*<<< orphan*/  ct_bcnt_resid; int /*<<< orphan*/  ct_cmd_resp; int /*<<< orphan*/  ct_reserved0; int /*<<< orphan*/  ct_options; int /*<<< orphan*/  ct_fcs_subtype; int /*<<< orphan*/  ct_fcs_type; int /*<<< orphan*/ * ct_in_id; int /*<<< orphan*/  ct_revision; } ;
typedef  TYPE_1__ ct_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOZPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isp_put_ct_hdr(ispsoftc_t *isp, ct_hdr_t *src, ct_hdr_t *dst)
{
	ISP_IOZPUT_8(isp, src->ct_revision, &dst->ct_revision);
	ISP_IOZPUT_8(isp, src->ct_in_id[0], &dst->ct_in_id[0]);
	ISP_IOZPUT_8(isp, src->ct_in_id[1], &dst->ct_in_id[1]);
	ISP_IOZPUT_8(isp, src->ct_in_id[2], &dst->ct_in_id[2]);
	ISP_IOZPUT_8(isp, src->ct_fcs_type, &dst->ct_fcs_type);
	ISP_IOZPUT_8(isp, src->ct_fcs_subtype, &dst->ct_fcs_subtype);
	ISP_IOZPUT_8(isp, src->ct_options, &dst->ct_options);
	ISP_IOZPUT_8(isp, src->ct_reserved0, &dst->ct_reserved0);
	ISP_IOZPUT_16(isp, src->ct_cmd_resp, &dst->ct_cmd_resp);
	ISP_IOZPUT_16(isp, src->ct_bcnt_resid, &dst->ct_bcnt_resid);
	ISP_IOZPUT_8(isp, src->ct_reserved1, &dst->ct_reserved1);
	ISP_IOZPUT_8(isp, src->ct_reason, &dst->ct_reason);
	ISP_IOZPUT_8(isp, src->ct_explanation, &dst->ct_explanation);
	ISP_IOZPUT_8(isp, src->ct_vunique, &dst->ct_vunique);
}