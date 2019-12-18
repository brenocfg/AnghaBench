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
struct usb_page_search {int /*<<< orphan*/  physaddr; struct uhci_td* buffer; } ;
struct usb_page_cache {int dummy; } ;
struct uhci_td {int td_self; struct usb_page_cache* page_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  UHCI_PTR_TD ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 

__attribute__((used)) static struct uhci_td *
uhci_init_td(struct usb_page_cache *pc)
{
	struct usb_page_search buf_res;
	struct uhci_td *td;

	usbd_get_page(pc, 0, &buf_res);

	td = buf_res.buffer;

	td->td_self =
	    htole32(buf_res.physaddr) |
	    htole32(UHCI_PTR_TD);

	td->page_cache = pc;

	return (td);
}