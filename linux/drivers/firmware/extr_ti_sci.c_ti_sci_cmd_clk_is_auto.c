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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ti_sci_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MSG_CLOCK_SW_STATE_AUTO ; 
 int ti_sci_cmd_get_clock_state (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_sci_cmd_clk_is_auto(const struct ti_sci_handle *handle,
				  u32 dev_id, u32 clk_id, bool *req_state)
{
	u8 state = 0;
	int ret;

	if (!req_state)
		return -EINVAL;

	ret = ti_sci_cmd_get_clock_state(handle, dev_id, clk_id, &state, NULL);
	if (ret)
		return ret;

	*req_state = (state == MSG_CLOCK_SW_STATE_AUTO);
	return 0;
}