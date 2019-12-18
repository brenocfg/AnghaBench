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
struct usb_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
octusb_get_dma_delay(struct usb_device *udev, uint32_t *pus)
{
	/* DMA delay - wait until any use of memory is finished */
	*pus = (2125);			/* microseconds */
}