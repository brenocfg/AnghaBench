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
struct clk_rpm {int enabled; int /*<<< orphan*/  rpm_clk_id; int /*<<< orphan*/  rpm; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_RPM_ACTIVE_STATE ; 
 int qcom_rpm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct clk_rpm* to_clk_rpm (struct clk_hw*) ; 

__attribute__((used)) static void clk_rpm_fixed_unprepare(struct clk_hw *hw)
{
	struct clk_rpm *r = to_clk_rpm(hw);
	u32 value = 0;
	int ret;

	ret = qcom_rpm_write(r->rpm, QCOM_RPM_ACTIVE_STATE,
			     r->rpm_clk_id, &value, 1);
	if (!ret)
		r->enabled = false;
}