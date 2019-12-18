#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 scalar_t__ IS_FC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_parse_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_parse_async_fc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isp_intr_async(ispsoftc_t *isp, uint16_t event)
{

	if (IS_FC(isp))
		isp_parse_async_fc(isp, event);
	else
		isp_parse_async(isp, event);
}