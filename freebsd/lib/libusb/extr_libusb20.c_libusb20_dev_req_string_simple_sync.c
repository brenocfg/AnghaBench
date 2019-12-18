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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  temp ;
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  isprint (char) ; 
 int libusb20_dev_req_string_sync (struct libusb20_device*,int,int,int*,int) ; 

int
libusb20_dev_req_string_simple_sync(struct libusb20_device *pdev,
    uint8_t str_index, void *ptr, uint16_t len)
{
	char *buf;
	int error;
	uint16_t langid;
	uint16_t n;
	uint16_t i;
	uint16_t c;
	uint8_t temp[255];
	uint8_t swap;

	/* the following code derives from the FreeBSD USB kernel */

	if ((len < 1) || (ptr == NULL)) {
		/* too short buffer */
		return (LIBUSB20_ERROR_INVALID_PARAM);
	}
	error = libusb20_dev_req_string_sync(pdev,
	    0, 0, temp, sizeof(temp));
	if (error < 0) {
		*(uint8_t *)ptr = 0;	/* zero terminate */
		return (error);
	}
	langid = temp[2] | (temp[3] << 8);

	error = libusb20_dev_req_string_sync(pdev, str_index,
	    langid, temp, sizeof(temp));
	if (error < 0) {
		*(uint8_t *)ptr = 0;	/* zero terminate */
		return (error);
	}
	if (temp[0] < 2) {
		/* string length is too short */
		*(uint8_t *)ptr = 0;	/* zero terminate */
		return (LIBUSB20_ERROR_OTHER);
	}
	/* reserve one byte for terminating zero */
	len--;

	/* find maximum length */
	n = (temp[0] / 2) - 1;
	if (n > len) {
		n = len;
	}
	/* reset swap state */
	swap = 3;

	/* setup output buffer pointer */
	buf = ptr;

	/* convert and filter */
	for (i = 0; (i != n); i++) {
		c = temp[(2 * i) + 2] | (temp[(2 * i) + 3] << 8);

		/* convert from Unicode, handle buggy strings */
		if (((c & 0xff00) == 0) && (swap & 1)) {
			/* Little Endian, default */
			*buf = c;
			swap = 1;
		} else if (((c & 0x00ff) == 0) && (swap & 2)) {
			/* Big Endian */
			*buf = c >> 8;
			swap = 2;
		} else {
			/* skip invalid character */
			continue;
		}
		/*
		 * Filter by default - we don't allow greater and less than
		 * signs because they might confuse the dmesg printouts!
		 */
		if ((*buf == '<') || (*buf == '>') || (!isprint(*buf))) {
			/* skip invalid character */
			continue;
		}
		buf++;
	}
	*buf = 0;			/* zero terminate string */

	return (0);
}