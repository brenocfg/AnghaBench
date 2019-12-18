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
 scalar_t__ MSG_DEVICE_HW_STATE_ON ; 
 scalar_t__ MSG_DEVICE_SW_STATE_ON ; 
 int ti_sci_get_device_state (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int ti_sci_cmd_dev_is_on(const struct ti_sci_handle *handle, u32 id,
				bool *r_state,  bool *curr_state)
{
	int ret;
	u8 p_state, c_state;

	if (!r_state && !curr_state)
		return -EINVAL;

	ret =
	    ti_sci_get_device_state(handle, id, NULL, NULL, &p_state, &c_state);
	if (ret)
		return ret;

	if (r_state)
		*r_state = (p_state == MSG_DEVICE_SW_STATE_ON);
	if (curr_state)
		*curr_state = (c_state == MSG_DEVICE_HW_STATE_ON);

	return 0;
}