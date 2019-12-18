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
typedef  int u32 ;
struct rpm_cc {int xo_buffer_value; int /*<<< orphan*/  xo_lock; } ;
struct clk_rpm {int rpm_clk_id; int xo_offset; int enabled; int /*<<< orphan*/  rpm; struct rpm_cc* rpm_cc; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_RPM_ACTIVE_STATE ; 
 int QCOM_RPM_XO_MODE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qcom_rpm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 struct clk_rpm* to_clk_rpm (struct clk_hw*) ; 

__attribute__((used)) static int clk_rpm_xo_prepare(struct clk_hw *hw)
{
	struct clk_rpm *r = to_clk_rpm(hw);
	struct rpm_cc *rcc = r->rpm_cc;
	int ret, clk_id = r->rpm_clk_id;
	u32 value;

	mutex_lock(&rcc->xo_lock);

	value = rcc->xo_buffer_value | (QCOM_RPM_XO_MODE_ON << r->xo_offset);
	ret = qcom_rpm_write(r->rpm, QCOM_RPM_ACTIVE_STATE, clk_id, &value, 1);
	if (!ret) {
		r->enabled = true;
		rcc->xo_buffer_value = value;
	}

	mutex_unlock(&rcc->xo_lock);

	return ret;
}