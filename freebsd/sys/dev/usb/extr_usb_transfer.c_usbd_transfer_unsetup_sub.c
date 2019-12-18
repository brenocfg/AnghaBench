#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_timeout_t ;
typedef  scalar_t__ uint8_t ;
struct usb_xfer_root {int /*<<< orphan*/  memory_base; int /*<<< orphan*/  cv_drain; int /*<<< orphan*/  dma_parent_tag; struct usb_page_cache* xfer_page_cache_end; struct usb_page_cache* xfer_page_cache_start; struct usb_page_cache* dma_page_cache_end; struct usb_page_cache* dma_page_cache_start; TYPE_1__* bus; int /*<<< orphan*/ * done_m; int /*<<< orphan*/  done_p; int /*<<< orphan*/  udev; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_USB ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (scalar_t__) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dma_tag_unsetup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pc_dmamap_destroy (struct usb_page_cache*) ; 
 int /*<<< orphan*/  usb_pc_free_mem (struct usb_page_cache*) ; 
 int /*<<< orphan*/  usb_proc_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_get_dma_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbd_transfer_unsetup_sub(struct usb_xfer_root *info, uint8_t needs_delay)
{
#if USB_HAVE_BUSDMA
	struct usb_page_cache *pc;
#endif

	USB_BUS_LOCK_ASSERT(info->bus, MA_OWNED);

	/* wait for any outstanding DMA operations */

	if (needs_delay) {
		usb_timeout_t temp;
		temp = usbd_get_dma_delay(info->udev);
		if (temp != 0) {
			usb_pause_mtx(&info->bus->bus_mtx,
			    USB_MS_TO_TICKS(temp));
		}
	}

	/* make sure that our done messages are not queued anywhere */
	usb_proc_mwait(info->done_p, &info->done_m[0], &info->done_m[1]);

	USB_BUS_UNLOCK(info->bus);

#if USB_HAVE_BUSDMA
	/* free DMA'able memory, if any */
	pc = info->dma_page_cache_start;
	while (pc != info->dma_page_cache_end) {
		usb_pc_free_mem(pc);
		pc++;
	}

	/* free DMA maps in all "xfer->frbuffers" */
	pc = info->xfer_page_cache_start;
	while (pc != info->xfer_page_cache_end) {
		usb_pc_dmamap_destroy(pc);
		pc++;
	}

	/* free all DMA tags */
	usb_dma_tag_unsetup(&info->dma_parent_tag);
#endif

	cv_destroy(&info->cv_drain);

	/*
	 * free the "memory_base" last, hence the "info" structure is
	 * contained within the "memory_base"!
	 */
	free(info->memory_base, M_USB);
}