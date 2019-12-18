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
struct TYPE_4__ {int /*<<< orphan*/ * snscb_wwn; int /*<<< orphan*/  snscb_cthdr; } ;
typedef  TYPE_1__ sns_gxn_id_rsp_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_get_ct_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_get_gxn_id_response(ispsoftc_t *isp, sns_gxn_id_rsp_t *src, sns_gxn_id_rsp_t *dst)
{
	int i;

	isp_get_ct_hdr(isp, &src->snscb_cthdr, &dst->snscb_cthdr);
	for (i = 0; i < 8; i++)
		ISP_IOZGET_8(isp, &src->snscb_wwn[i], dst->snscb_wwn[i]);
}