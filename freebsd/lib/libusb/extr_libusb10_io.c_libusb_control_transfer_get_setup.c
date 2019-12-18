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
struct libusb_transfer {scalar_t__ buffer; } ;
struct libusb_control_setup {int dummy; } ;

/* Variables and functions */

struct libusb_control_setup *
libusb_control_transfer_get_setup(struct libusb_transfer *transfer)
{
	return ((struct libusb_control_setup *)transfer->buffer);
}