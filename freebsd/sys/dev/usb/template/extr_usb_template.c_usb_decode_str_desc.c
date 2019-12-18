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
struct usb_string_descriptor {int bLength; int /*<<< orphan*/ * bString; } ;

/* Variables and functions */
 char UGETW (int /*<<< orphan*/ ) ; 

void
usb_decode_str_desc(struct usb_string_descriptor *sd, char *buf, size_t buflen)
{
	size_t i;

	if (sd->bLength < 2) {
		buf[0] = '\0';
		return;
	}

	for (i = 0; i < buflen - 1 && i < (sd->bLength / 2) - 1; i++)
		buf[i] = UGETW(sd->bString[i]);

	buf[i] = '\0';
}