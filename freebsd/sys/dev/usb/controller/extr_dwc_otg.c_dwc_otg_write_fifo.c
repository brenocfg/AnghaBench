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
typedef  int uint32_t ;
struct usb_page_search {int length; scalar_t__* buffer; } ;
struct usb_page_cache {int dummy; } ;
struct dwc_otg_softc {scalar_t__* sc_bounce_buffer; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_region_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 scalar_t__ usb_pc_buffer_is_aligned (struct usb_page_cache*,int,int,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int,struct usb_page_search*) ; 

__attribute__((used)) static void
dwc_otg_write_fifo(struct dwc_otg_softc *sc, struct usb_page_cache *pc,
    uint32_t offset, uint32_t fifo, uint32_t count)
{
	uint32_t temp;

	/* round down length to nearest 4-bytes */
	temp = count & ~3;

	/* check if we can write the data directly */
	if (temp != 0 && usb_pc_buffer_is_aligned(pc, offset, temp, 3)) {
		struct usb_page_search buf_res;

		/* pre-subtract length */
		count -= temp;

		/* iterate buffer list */
		do {
			/* get current buffer pointer */
			usbd_get_page(pc, offset, &buf_res);

			if (buf_res.length > temp)
				buf_res.length = temp;

			/* transfer data into FIFO */
			bus_space_write_region_4(sc->sc_io_tag, sc->sc_io_hdl,
			    fifo, buf_res.buffer, buf_res.length / 4);

			offset += buf_res.length;
			fifo += buf_res.length;
			temp -= buf_res.length;
		} while (temp != 0);
	}

	/* check for remainder */
	if (count != 0) {
		/* clear topmost word before copy */
		sc->sc_bounce_buffer[(count - 1) / 4] = 0;

		/* copy out data */
		usbd_copy_out(pc, offset,
		    sc->sc_bounce_buffer, count);

		/* transfer data into FIFO */
		bus_space_write_region_4(sc->sc_io_tag,
		    sc->sc_io_hdl, fifo, sc->sc_bounce_buffer,
		    (count + 3) / 4);
	}
}