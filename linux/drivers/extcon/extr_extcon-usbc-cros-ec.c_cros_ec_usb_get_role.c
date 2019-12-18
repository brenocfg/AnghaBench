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
struct ec_response_usb_pd_control_v1 {int enabled; int polarity; int role; } ;
struct ec_params_usb_pd_control {int /*<<< orphan*/  swap; int /*<<< orphan*/  mux; int /*<<< orphan*/  role; int /*<<< orphan*/  port; } ;
struct cros_ec_extcon_info {int /*<<< orphan*/  port_id; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  pd_control ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_USB_PD_CONTROL ; 
 int ENOTCONN ; 
 int PD_CTRL_RESP_ENABLED_CONNECTED ; 
 int /*<<< orphan*/  USB_PD_CTRL_MUX_NO_CHANGE ; 
 int /*<<< orphan*/  USB_PD_CTRL_ROLE_NO_CHANGE ; 
 int /*<<< orphan*/  USB_PD_CTRL_SWAP_NONE ; 
 int cros_ec_pd_command (struct cros_ec_extcon_info*,int /*<<< orphan*/ ,int,struct ec_params_usb_pd_control*,int,struct ec_response_usb_pd_control_v1*,int) ; 

__attribute__((used)) static int cros_ec_usb_get_role(struct cros_ec_extcon_info *info,
				bool *polarity)
{
	struct ec_params_usb_pd_control pd_control;
	struct ec_response_usb_pd_control_v1 resp;
	int ret;

	pd_control.port = info->port_id;
	pd_control.role = USB_PD_CTRL_ROLE_NO_CHANGE;
	pd_control.mux = USB_PD_CTRL_MUX_NO_CHANGE;
	pd_control.swap = USB_PD_CTRL_SWAP_NONE;
	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_CONTROL, 1,
				 &pd_control, sizeof(pd_control),
				 &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	if (!(resp.enabled & PD_CTRL_RESP_ENABLED_CONNECTED))
		return -ENOTCONN;

	*polarity = resp.polarity;

	return resp.role;
}