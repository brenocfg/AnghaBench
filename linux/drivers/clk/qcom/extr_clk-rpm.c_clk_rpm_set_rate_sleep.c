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
struct clk_rpm {int /*<<< orphan*/  rpm_clk_id; int /*<<< orphan*/  rpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  QCOM_RPM_SLEEP_STATE ; 
 int qcom_rpm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int clk_rpm_set_rate_sleep(struct clk_rpm *r, unsigned long rate)
{
	u32 value = DIV_ROUND_UP(rate, 1000); /* to kHz */

	return qcom_rpm_write(r->rpm, QCOM_RPM_SLEEP_STATE,
			      r->rpm_clk_id, &value, 1);
}