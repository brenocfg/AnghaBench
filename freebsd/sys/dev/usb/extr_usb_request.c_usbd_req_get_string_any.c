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
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ no_strings; } ;
struct usb_device {int /*<<< orphan*/  langid; TYPE_1__ flags; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int UGETW (scalar_t__*) ; 
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ USB_ERR_NORMAL_COMPLETION ; 
 scalar_t__ USB_ERR_STALLED ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ usbd_req_get_string_desc (struct usb_device*,struct mtx*,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 

usb_error_t
usbd_req_get_string_any(struct usb_device *udev, struct mtx *mtx, char *buf,
    uint16_t len, uint8_t string_index)
{
	char *s;
	uint8_t *temp;
	uint16_t i;
	uint16_t n;
	uint16_t c;
	uint8_t swap;
	usb_error_t err;

	if (len == 0) {
		/* should not happen */
		return (USB_ERR_NORMAL_COMPLETION);
	}
	if (string_index == 0) {
		/* this is the language table */
		buf[0] = 0;
		return (USB_ERR_INVAL);
	}
	if (udev->flags.no_strings) {
		buf[0] = 0;
		return (USB_ERR_STALLED);
	}
	err = usbd_req_get_string_desc
	    (udev, mtx, buf, len, udev->langid, string_index);
	if (err) {
		buf[0] = 0;
		return (err);
	}
	temp = (uint8_t *)buf;

	if (temp[0] < 2) {
		/* string length is too short */
		buf[0] = 0;
		return (USB_ERR_INVAL);
	}
	/* reserve one byte for terminating zero */
	len--;

	/* find maximum length */
	s = buf;
	n = (temp[0] / 2) - 1;
	if (n > len) {
		n = len;
	}
	/* skip descriptor header */
	temp += 2;

	/* reset swap state */
	swap = 3;

	/* convert and filter */
	for (i = 0; (i != n); i++) {
		c = UGETW(temp + (2 * i));

		/* convert from Unicode, handle buggy strings */
		if (((c & 0xff00) == 0) && (swap & 1)) {
			/* Little Endian, default */
			*s = c;
			swap = 1;
		} else if (((c & 0x00ff) == 0) && (swap & 2)) {
			/* Big Endian */
			*s = c >> 8;
			swap = 2;
		} else {
			/* silently skip bad character */
			continue;
		}

		/*
		 * Filter by default - We only allow alphanumerical
		 * and a few more to avoid any problems with scripts
		 * and daemons.
		 */
		if (isalpha(*s) ||
		    isdigit(*s) ||
		    *s == '-' ||
		    *s == '+' ||
		    *s == ' ' ||
		    *s == '.' ||
		    *s == ',' ||
		    *s == ':' ||
		    *s == '/' ||
		    *s == '(' ||
		    *s == ')') {
			/* allowed */
			s++;
		}
		/* silently skip bad character */
	}
	*s = 0;				/* zero terminate resulting string */
	return (USB_ERR_NORMAL_COMPLETION);
}