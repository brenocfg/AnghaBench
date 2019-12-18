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
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ snprintf (char*,int,char*,int,int) ; 

void
usb_printbcd(char *p, uint16_t p_len, uint16_t bcd)
{
	if (snprintf(p, p_len, "%x.%02x", bcd >> 8, bcd & 0xff)) {
		/* ignore any errors */
	}
}