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
struct TYPE_4__ {int /*<<< orphan*/  snscb_flags; int /*<<< orphan*/  snscb_area; int /*<<< orphan*/  snscb_domain; int /*<<< orphan*/  snscb_port_type; int /*<<< orphan*/  snscb_reserved3; int /*<<< orphan*/  snscb_mword_div_2; int /*<<< orphan*/  snscb_cmd; int /*<<< orphan*/  snscb_reserved1; int /*<<< orphan*/  snscb_sblen; int /*<<< orphan*/ * snscb_addr; int /*<<< orphan*/  snscb_reserved0; int /*<<< orphan*/  snscb_rblen; } ;
typedef  TYPE_1__ sns_gid_pt_req_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isp_put_gid_pt_request(ispsoftc_t *isp, sns_gid_pt_req_t *src, sns_gid_pt_req_t *dst)
{
	ISP_IOXPUT_16(isp, src->snscb_rblen, &dst->snscb_rblen);
	ISP_IOXPUT_16(isp, src->snscb_reserved0, &dst->snscb_reserved0);
	ISP_IOXPUT_16(isp, src->snscb_addr[0], &dst->snscb_addr[0]);
	ISP_IOXPUT_16(isp, src->snscb_addr[1], &dst->snscb_addr[1]);
	ISP_IOXPUT_16(isp, src->snscb_addr[2], &dst->snscb_addr[2]);
	ISP_IOXPUT_16(isp, src->snscb_addr[3], &dst->snscb_addr[3]);
	ISP_IOXPUT_16(isp, src->snscb_sblen, &dst->snscb_sblen);
	ISP_IOXPUT_16(isp, src->snscb_reserved1, &dst->snscb_reserved1);
	ISP_IOXPUT_16(isp, src->snscb_cmd, &dst->snscb_cmd);
	ISP_IOXPUT_16(isp, src->snscb_mword_div_2, &dst->snscb_mword_div_2);
	ISP_IOXPUT_32(isp, src->snscb_reserved3, &dst->snscb_reserved3);
	ISP_IOXPUT_8(isp, src->snscb_port_type, &dst->snscb_port_type);
	ISP_IOXPUT_8(isp, src->snscb_domain, &dst->snscb_domain);
	ISP_IOXPUT_8(isp, src->snscb_area, &dst->snscb_area);
	ISP_IOXPUT_8(isp, src->snscb_flags, &dst->snscb_flags);
}