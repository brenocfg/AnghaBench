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
typedef  int /*<<< orphan*/  u32 ;
struct clk_rpm {scalar_t__ rpm_clk_id; int /*<<< orphan*/  rpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  QCOM_RPM_ACTIVE_STATE ; 
 scalar_t__ QCOM_RPM_CXO_BUFFERS ; 
 scalar_t__ QCOM_RPM_PLL_4 ; 
 int /*<<< orphan*/  QCOM_RPM_SLEEP_STATE ; 
 int qcom_rpm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int clk_rpm_handoff(struct clk_rpm *r)
{
	int ret;
	u32 value = INT_MAX;

	/*
	 * The vendor tree simply reads the status for this
	 * RPM clock.
	 */
	if (r->rpm_clk_id == QCOM_RPM_PLL_4 ||
		r->rpm_clk_id == QCOM_RPM_CXO_BUFFERS)
		return 0;

	ret = qcom_rpm_write(r->rpm, QCOM_RPM_ACTIVE_STATE,
			     r->rpm_clk_id, &value, 1);
	if (ret)
		return ret;
	ret = qcom_rpm_write(r->rpm, QCOM_RPM_SLEEP_STATE,
			     r->rpm_clk_id, &value, 1);
	if (ret)
		return ret;

	return 0;
}