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
struct usb_gen_descriptor {int ugd_maxlen; int ugd_actlen; void* ugd_data; } ;
typedef  int /*<<< orphan*/ * report_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_GET_REPORT_DESC ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/ * hid_get_report_desc_compat7 (int) ; 
 void* hid_pass_ptr (void*) ; 
 int /*<<< orphan*/ * hid_use_report_desc (void*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct usb_gen_descriptor*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (struct usb_gen_descriptor*,int /*<<< orphan*/ ,int) ; 

report_desc_t
hid_get_report_desc(int fd)
{
	struct usb_gen_descriptor ugd;
	report_desc_t rep;
	void *data;

	memset(&ugd, 0, sizeof(ugd));

	/* get actual length first */
	ugd.ugd_data = hid_pass_ptr(NULL);
	ugd.ugd_maxlen = 65535;
	if (ioctl(fd, USB_GET_REPORT_DESC, &ugd) < 0) {
#ifdef HID_COMPAT7
		/* could not read descriptor */
		/* try FreeBSD 7 compat code */
		return (hid_get_report_desc_compat7(fd));
#else
		return (NULL);
#endif
	}

	/*
	 * NOTE: The kernel will return a failure if 
	 * "ugd_actlen" is zero.
	 */
	data = malloc(ugd.ugd_actlen);
	if (data == NULL)
		return (NULL);

	/* fetch actual descriptor */
	ugd.ugd_data = hid_pass_ptr(data);
	ugd.ugd_maxlen = ugd.ugd_actlen;
	if (ioctl(fd, USB_GET_REPORT_DESC, &ugd) < 0) {
		/* could not read descriptor */
		free(data);
		return (NULL);
	}

	/* sanity check */
	if (ugd.ugd_actlen < 1) {
		/* invalid report descriptor */
		free(data);
		return (NULL);
	}

	/* check END_COLLECTION */
	if (((unsigned char *)data)[ugd.ugd_actlen -1] != 0xC0) {
		/* invalid end byte */
		free(data);
		return (NULL);
	}

	rep = hid_use_report_desc(data, ugd.ugd_actlen);

	free(data);

	return (rep);
}