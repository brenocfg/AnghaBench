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
struct TYPE_4__ {int /*<<< orphan*/ * rftid_fc4types; int /*<<< orphan*/ * rftid_portid; int /*<<< orphan*/  rftid_reserved; int /*<<< orphan*/  rftid_hdr; } ;
typedef  TYPE_1__ rft_id_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOZPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_ct_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_rft_id(ispsoftc_t *isp, rft_id_t *src, rft_id_t *dst)
{
	int i;
	isp_put_ct_hdr(isp, &src->rftid_hdr, &dst->rftid_hdr);
	ISP_IOZPUT_8(isp, src->rftid_reserved, &dst->rftid_reserved);
	for (i = 0; i < 3; i++) {
		ISP_IOZPUT_8(isp, src->rftid_portid[i], &dst->rftid_portid[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOZPUT_32(isp, src->rftid_fc4types[i], &dst->rftid_fc4types[i]);
	}
}