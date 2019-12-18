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
typedef  int /*<<< orphan*/  (* usb_bus_mem_cb_t ) (struct usb_bus*,int /*<<< orphan*/ *) ;
struct usb_bus {int /*<<< orphan*/  bus_spin_lock; int /*<<< orphan*/  bus_mtx; int /*<<< orphan*/  dma_parent_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all_cb ; 
 int /*<<< orphan*/  usb_dma_tag_unsetup (int /*<<< orphan*/ ) ; 

void
usb_bus_mem_free_all(struct usb_bus *bus, usb_bus_mem_cb_t *cb)
{
#if USB_HAVE_BUSDMA
	if (cb) {
		cb(bus, &usb_bus_mem_free_all_cb);
	}
	usb_dma_tag_unsetup(bus->dma_parent_tag);
#endif

	mtx_destroy(&bus->bus_mtx);
	mtx_destroy(&bus->bus_spin_lock);
}