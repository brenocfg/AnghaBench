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
struct TYPE_4__ {int /*<<< orphan*/  vp_global_options; int /*<<< orphan*/  vp_count; } ;
typedef  TYPE_1__ isp_icb_2400_vpinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isp_put_icb_2400_vpinfo(ispsoftc_t *isp, isp_icb_2400_vpinfo_t *src, isp_icb_2400_vpinfo_t *dst)
{
	ISP_IOXPUT_16(isp, src->vp_count, &dst->vp_count);
	ISP_IOXPUT_16(isp, src->vp_global_options, &dst->vp_global_options);
}