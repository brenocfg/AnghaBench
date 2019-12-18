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
struct mrfld_extcon_data {int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 unsigned int INTEL_USB_ID_GND ; 
 unsigned int INTEL_USB_RID_A ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mrfld_extcon_get_id (struct mrfld_extcon_data*) ; 

__attribute__((used)) static int mrfld_extcon_role_detect(struct mrfld_extcon_data *data)
{
	unsigned int id;
	bool usb_host;
	int ret;

	ret = mrfld_extcon_get_id(data);
	if (ret < 0)
		return ret;

	id = ret;

	usb_host = (id == INTEL_USB_ID_GND) || (id == INTEL_USB_RID_A);
	extcon_set_state_sync(data->edev, EXTCON_USB_HOST, usb_host);

	return 0;
}