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
 void* USB_ADD_BYTES (void const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,scalar_t__,struct usb_page_search*) ; 

void
usbd_copy_in(struct usb_page_cache *cache, usb_frlength_t offset,
    const void *ptr, usb_frlength_t len)
{
	struct usb_page_search buf_res;

	while (len != 0) {

		usbd_get_page(cache, offset, &buf_res);

		if (buf_res.length > len) {
			buf_res.length = len;
		}
		memcpy(buf_res.buffer, ptr, buf_res.length);

		offset += buf_res.length;
		len -= buf_res.length;
		ptr = USB_ADD_BYTES(ptr, buf_res.length);
	}
}