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
struct TYPE_4__ {int /*<<< orphan*/ * req_sense_data; int /*<<< orphan*/  req_header; } ;
typedef  TYPE_1__ ispstatus_cont_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOZGET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_24XX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_get_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_get_cont_response(ispsoftc_t *isp, ispstatus_cont_t *src, ispstatus_cont_t *dst)
{
	int i;
	isp_get_hdr(isp, &src->req_header, &dst->req_header);
	if (IS_24XX(isp)) {
		uint32_t *a, *b;
		a = (uint32_t *) src->req_sense_data;
		b = (uint32_t *) dst->req_sense_data;
		for (i = 0; i < (sizeof (src->req_sense_data) / sizeof (uint32_t)); i++) {
			ISP_IOZGET_32(isp, a++, *b++);
		}
	} else {
		for (i = 0; i < sizeof (src->req_sense_data); i++) {
			ISP_IOXGET_8(isp, &src->req_sense_data[i], dst->req_sense_data[i]);
		}
	}
}