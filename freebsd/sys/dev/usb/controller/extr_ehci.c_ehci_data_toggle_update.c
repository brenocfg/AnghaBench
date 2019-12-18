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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_xfer {int max_packet_size; TYPE_1__* endpoint; } ;
struct TYPE_2__ {int toggle_next; } ;

/* Variables and functions */

__attribute__((used)) static void
ehci_data_toggle_update(struct usb_xfer *xfer, uint16_t actlen, uint16_t xlen)
{
	uint16_t rem;
	uint8_t dt;

	/* count number of full packets */
	dt = (actlen / xfer->max_packet_size) & 1;

	/* compute remainder */
	rem = actlen % xfer->max_packet_size;

	if (rem > 0)
		dt ^= 1;	/* short packet at the end */
	else if (actlen != xlen)
		dt ^= 1;	/* zero length packet at the end */
	else if (xlen == 0)
		dt ^= 1;	/* zero length transfer */

	xfer->endpoint->toggle_next ^= dt;
}