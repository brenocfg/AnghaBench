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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int ELANTECH_CUSTOM_CMD ; 
 scalar_t__ PSM_ACK ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mouse_ext_command (int /*<<< orphan*/ ,int) ; 
 scalar_t__ send_aux_command (int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_mouse_scaling (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
elantech_cmd(KBDC kbdc, int hwversion, int cmd, int *resp)
{
	int res;

	if (hwversion == 2) {
		res = set_mouse_scaling(kbdc, 1) == 0;
		res |= mouse_ext_command(kbdc, cmd) == 0;
	} else {
		res = send_aux_command(kbdc, ELANTECH_CUSTOM_CMD) != PSM_ACK;
		res |= send_aux_command(kbdc, cmd) != PSM_ACK;
	}
	res |= get_mouse_status(kbdc, resp, 0, 3) != 3;

	return (res);
}