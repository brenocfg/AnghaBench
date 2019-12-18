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
typedef  scalar_t__ usb_frlength_t ;
struct usb_page_search {scalar_t__ length; int /*<<< orphan*/  buffer; } ;
struct usb_page_cache {int dummy; } ;

/* Variables and functions */
 void* USB_ADD_BYTES (void*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,scalar_t__,struct usb_page_search*) ; 

void
usbd_copy_out(struct usb_page_cache *cache, usb_frlength_t offset,
    void *ptr, usb_frlength_t len)
{
	struct usb_page_search res;

	while (len != 0) {

		usbd_get_page(cache, offset, &res);

		if (res.length > len) {
			res.length = len;
		}
		memcpy(ptr, res.buffer, res.length);

		offset += res.length;
		len -= res.length;
		ptr = USB_ADD_BYTES(ptr, res.length);
	}
}