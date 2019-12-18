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
typedef  int /*<<< orphan*/  usb_interface_descriptor_t ;
typedef  int /*<<< orphan*/  usb_config_descriptor_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * USBD_ParseConfigurationDescriptorEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static usb_interface_descriptor_t *
USBD_ParseConfigurationDescriptor(usb_config_descriptor_t *conf,
	uint8_t intfnum, uint8_t altset)
{

	return USBD_ParseConfigurationDescriptorEx(conf, conf, intfnum, altset,
	    -1, -1, -1);
}