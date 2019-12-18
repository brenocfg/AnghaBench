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
struct ec_response_usb_pd_power_info {int type; } ;
struct ec_params_usb_pd_power_info {int /*<<< orphan*/  port; } ;
struct cros_ec_extcon_info {int /*<<< orphan*/  port_id; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_USB_PD_POWER_INFO ; 
 int cros_ec_pd_command (struct cros_ec_extcon_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ec_params_usb_pd_power_info*,int,struct ec_response_usb_pd_power_info*,int) ; 

__attribute__((used)) static int cros_ec_usb_get_power_type(struct cros_ec_extcon_info *info)
{
	struct ec_params_usb_pd_power_info req;
	struct ec_response_usb_pd_power_info resp;
	int ret;

	req.port = info->port_id;
	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_POWER_INFO, 0,
				 &req, sizeof(req), &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	return resp.type;
}