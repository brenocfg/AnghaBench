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
typedef  int /*<<< orphan*/  uint32_t ;
struct libusb_transfer {int num_iso_packets; TYPE_1__* iso_packet_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */

void
libusb_set_iso_packet_lengths(struct libusb_transfer *transfer, uint32_t length)
{
	int n;

	if (transfer->num_iso_packets < 0)
		return;

	for (n = 0; n != transfer->num_iso_packets; n++)
		transfer->iso_packet_desc[n].length = length;
}