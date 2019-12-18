#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_3__ {int /*<<< orphan*/  rqs_entry_type; int /*<<< orphan*/  rqs_entry_count; } ;
typedef  TYPE_1__ isphdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ISP_IS_SBUS (int /*<<< orphan*/ *) ; 

int
isp_get_response_type(ispsoftc_t *isp, isphdr_t *hp)
{
	uint8_t type;
	if (ISP_IS_SBUS(isp)) {
		ISP_IOXGET_8(isp, &hp->rqs_entry_count, type);
	} else {
		ISP_IOXGET_8(isp, &hp->rqs_entry_type, type);
	}
	return ((int)type);
}