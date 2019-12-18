#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_config_descriptor_t ;
struct TYPE_3__ {int /*<<< orphan*/  uuh_len; } ;
struct TYPE_4__ {TYPE_1__ usc_hdr; } ;
union usbd_urb {TYPE_2__ uu_selconf; } ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usbd_interface_list_entry {int /*<<< orphan*/  uil_intfdesc; } ;

/* Variables and functions */
 union usbd_urb* USBD_CreateConfigurationRequestEx (int /*<<< orphan*/ *,struct usbd_interface_list_entry*) ; 
 int /*<<< orphan*/  USBD_ParseConfigurationDescriptorEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  bzero (struct usbd_interface_list_entry*,int) ; 

__attribute__((used)) static union usbd_urb *
USBD_CreateConfigurationRequest(usb_config_descriptor_t *conf, uint16_t *len)
{
	struct usbd_interface_list_entry list[2];
	union usbd_urb *urb;

	bzero(list, sizeof(struct usbd_interface_list_entry) * 2);
	list[0].uil_intfdesc = USBD_ParseConfigurationDescriptorEx(conf, conf,
	    -1, -1, -1, -1, -1);
	urb = USBD_CreateConfigurationRequestEx(conf, list);
	if (urb == NULL)
		return (NULL);

	*len = urb->uu_selconf.usc_hdr.uuh_len;
	return (urb);
}