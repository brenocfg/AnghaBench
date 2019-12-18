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
struct ti_sci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_CLOCK_SW_STATE_UNREQ ; 
 int ti_sci_set_clock_state (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_sci_cmd_idle_clock(const struct ti_sci_handle *handle,
				 u32 dev_id, u32 clk_id)
{
	return ti_sci_set_clock_state(handle, dev_id, clk_id, 0,
				      MSG_CLOCK_SW_STATE_UNREQ);
}