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
struct TYPE_4__ {int /*<<< orphan*/  pnhle_reserved; int /*<<< orphan*/  pnhle_handle; int /*<<< orphan*/  pnhle_port_id_hi; int /*<<< orphan*/  pnhle_port_id_lo; } ;
typedef  TYPE_1__ isp_pnhle_24xx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isp_get_pnhle_24xx(ispsoftc_t *isp, isp_pnhle_24xx_t *src, isp_pnhle_24xx_t *dst)
{

	ISP_IOXGET_16(isp, &src->pnhle_port_id_lo, dst->pnhle_port_id_lo);
	ISP_IOXGET_16(isp, &src->pnhle_port_id_hi, dst->pnhle_port_id_hi);
	ISP_IOXGET_16(isp, &src->pnhle_handle, dst->pnhle_handle);
	ISP_IOXGET_16(isp, &src->pnhle_reserved, dst->pnhle_reserved);
}