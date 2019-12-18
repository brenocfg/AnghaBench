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
typedef  int /*<<< orphan*/  ugd ;
struct usb_gen_descriptor {unsigned int ugd_maxlen; int ugd_report_type; int /*<<< orphan*/  ugd_data; } ;
typedef  enum hid_kind { ____Placeholder_hid_kind } hid_kind ;

/* Variables and functions */
 int /*<<< orphan*/  USB_GET_REPORT ; 
 int /*<<< orphan*/  hid_pass_ptr (unsigned char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct usb_gen_descriptor*) ; 
 int /*<<< orphan*/  memset (struct usb_gen_descriptor*,int /*<<< orphan*/ ,int) ; 

int
hid_get_report(int fd, enum hid_kind k, unsigned char *data, unsigned int size)
{
	struct usb_gen_descriptor ugd;

	memset(&ugd, 0, sizeof(ugd));
	ugd.ugd_data = hid_pass_ptr(data);
	ugd.ugd_maxlen = size;
	ugd.ugd_report_type = k + 1;
	return (ioctl(fd, USB_GET_REPORT, &ugd));
}