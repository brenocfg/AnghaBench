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
struct usb_page_search {int /*<<< orphan*/  physaddr; struct ohci_ed* buffer; } ;
struct usb_page_cache {int dummy; } ;
struct ohci_ed {struct usb_page_cache* page_cache; void* ed_flags; void* ed_self; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_ED_SKIP ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 

__attribute__((used)) static struct ohci_ed *
ohci_init_ed(struct usb_page_cache *pc)
{
	struct usb_page_search buf_res;
	struct ohci_ed *ed;

	usbd_get_page(pc, 0, &buf_res);

	ed = buf_res.buffer;

	ed->ed_self = htole32(buf_res.physaddr);
	ed->ed_flags = htole32(OHCI_ED_SKIP);
	ed->page_cache = pc;

	return (ed);
}