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
struct TYPE_4__ {scalar_t__* snscb_data; scalar_t__ snscb_sblen; scalar_t__* snscb_addr; scalar_t__ snscb_rblen; } ;
typedef  TYPE_1__ sns_screq_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 

void
isp_put_sns_request(ispsoftc_t *isp, sns_screq_t *src, sns_screq_t *dst)
{
	int i, nw = (int) src->snscb_sblen;
	ISP_IOXPUT_16(isp, src->snscb_rblen, &dst->snscb_rblen);
	for (i = 0; i < 4; i++) {
		ISP_IOXPUT_16(isp, src->snscb_addr[i], &dst->snscb_addr[i]);
	}
	ISP_IOXPUT_16(isp, src->snscb_sblen, &dst->snscb_sblen);
	for (i = 0; i < nw; i++) {
		ISP_IOXPUT_16(isp, src->snscb_data[i], &dst->snscb_data[i]);
	}
}