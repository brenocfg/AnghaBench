#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* usb_bus_mem_cb_t ) (struct usb_bus*,int /*<<< orphan*/ *) ;
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct usb_bus {int alloc_failed; scalar_t__ devices_max; int /*<<< orphan*/ * devices; int /*<<< orphan*/  dma_bits; int /*<<< orphan*/  bus_mtx; int /*<<< orphan*/  dma_tags; int /*<<< orphan*/  dma_parent_tag; TYPE_1__ intr_q; int /*<<< orphan*/  power_wdog; int /*<<< orphan*/  parent; int /*<<< orphan*/  bus_spin_lock; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int MTX_SPIN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_DMA_TAG_MAX ; 
 scalar_t__ USB_MAX_DEVICES ; 
 scalar_t__ USB_MIN_DEVICES ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_bus_mem_alloc_all_cb ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (struct usb_bus*,int /*<<< orphan*/  (*) (struct usb_bus*,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dma_tag_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint8_t
usb_bus_mem_alloc_all(struct usb_bus *bus, bus_dma_tag_t dmat,
    usb_bus_mem_cb_t *cb)
{
	bus->alloc_failed = 0;

	mtx_init(&bus->bus_mtx, device_get_nameunit(bus->parent),
	    "usb_def_mtx", MTX_DEF | MTX_RECURSE);

	mtx_init(&bus->bus_spin_lock, device_get_nameunit(bus->parent),
	    "usb_spin_mtx", MTX_SPIN | MTX_RECURSE);

	usb_callout_init_mtx(&bus->power_wdog,
	    &bus->bus_mtx, 0);

	TAILQ_INIT(&bus->intr_q.head);

#if USB_HAVE_BUSDMA
	usb_dma_tag_setup(bus->dma_parent_tag, bus->dma_tags,
	    dmat, &bus->bus_mtx, NULL, bus->dma_bits, USB_BUS_DMA_TAG_MAX);
#endif
	if ((bus->devices_max > USB_MAX_DEVICES) ||
	    (bus->devices_max < USB_MIN_DEVICES) ||
	    (bus->devices == NULL)) {
		DPRINTFN(0, "Devices field has not been "
		    "initialised properly\n");
		bus->alloc_failed = 1;		/* failure */
	}
#if USB_HAVE_BUSDMA
	if (cb) {
		cb(bus, &usb_bus_mem_alloc_all_cb);
	}
#endif
	if (bus->alloc_failed) {
		usb_bus_mem_free_all(bus, cb);
	}
	return (bus->alloc_failed);
}