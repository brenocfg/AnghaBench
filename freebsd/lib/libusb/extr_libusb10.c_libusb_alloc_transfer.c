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
typedef  int /*<<< orphan*/  uint8_t ;
struct libusb_transfer {int num_iso_packets; } ;
struct libusb_super_transfer {int dummy; } ;
typedef  int /*<<< orphan*/  libusb_iso_packet_descriptor ;

/* Variables and functions */
 struct libusb_super_transfer* malloc (int) ; 
 int /*<<< orphan*/  memset (struct libusb_super_transfer*,int /*<<< orphan*/ ,int) ; 

struct libusb_transfer *
libusb_alloc_transfer(int iso_packets)
{
	struct libusb_transfer *uxfer;
	struct libusb_super_transfer *sxfer;
	int len;

	len = sizeof(struct libusb_transfer) +
	    sizeof(struct libusb_super_transfer) +
	    (iso_packets * sizeof(libusb_iso_packet_descriptor));

	sxfer = malloc(len);
	if (sxfer == NULL)
		return (NULL);

	memset(sxfer, 0, len);

	uxfer = (struct libusb_transfer *)(
	    ((uint8_t *)sxfer) + sizeof(*sxfer));

	/* set default value */
	uxfer->num_iso_packets = iso_packets;

	return (uxfer);
}