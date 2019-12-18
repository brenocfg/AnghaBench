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
typedef  void* usb_size_t ;
typedef  void* usb_frlength_t ;
struct usb_page_search {void* physaddr; void* length; void* buffer; } ;
struct usb_page_cache {void* page_offset_buf; scalar_t__ buffer; scalar_t__ ismultiseg; struct usb_page* page_start; } ;
struct usb_page {void* physaddr; scalar_t__ buffer; } ;

/* Variables and functions */
 void* USB_ADD_BYTES (scalar_t__,void*) ; 
 void* USB_PAGE_SIZE ; 

void
usbd_get_page(struct usb_page_cache *pc, usb_frlength_t offset,
    struct usb_page_search *res)
{
#if USB_HAVE_BUSDMA
	struct usb_page *page;

	if (pc->page_start) {

		/* Case 1 - something has been loaded into DMA */

		if (pc->buffer) {

			/* Case 1a - Kernel Virtual Address */

			res->buffer = USB_ADD_BYTES(pc->buffer, offset);
		}
		offset += pc->page_offset_buf;

		/* compute destination page */

		page = pc->page_start;

		if (pc->ismultiseg) {

			page += (offset / USB_PAGE_SIZE);

			offset %= USB_PAGE_SIZE;

			res->length = USB_PAGE_SIZE - offset;
			res->physaddr = page->physaddr + offset;
		} else {
			res->length = (usb_size_t)-1;
			res->physaddr = page->physaddr + offset;
		}
		if (!pc->buffer) {

			/* Case 1b - Non Kernel Virtual Address */

			res->buffer = USB_ADD_BYTES(page->buffer, offset);
		}
		return;
	}
#endif
	/* Case 2 - Plain PIO */

	res->buffer = USB_ADD_BYTES(pc->buffer, offset);
	res->length = (usb_size_t)-1;
#if USB_HAVE_BUSDMA
	res->physaddr = 0;
#endif
}