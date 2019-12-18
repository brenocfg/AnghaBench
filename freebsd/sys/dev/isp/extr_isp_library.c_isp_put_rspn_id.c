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
struct TYPE_4__ {int /*<<< orphan*/  rspnid_length; int /*<<< orphan*/  rspnid_reserved; int /*<<< orphan*/  rspnid_hdr; } ;
typedef  TYPE_1__ rspn_id_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_ct_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_rspn_id(ispsoftc_t *isp, rspn_id_t *src, rspn_id_t *dst)
{
/*	int i;*/
	isp_put_ct_hdr(isp, &src->rspnid_hdr, &dst->rspnid_hdr);
	ISP_IOZPUT_8(isp, src->rspnid_reserved, &dst->rspnid_reserved);
	ISP_IOZPUT_8(isp, src->rspnid_length, &dst->rspnid_length);
/*	for (i = 0; i < src->rspnid_length; i++)
		ISP_IOZPUT_8(isp, src->rspnid_name[i], &dst->rspnid_name[i]);*/
}