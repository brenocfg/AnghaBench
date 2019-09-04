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

/* Variables and functions */
 int hexval (char const) ; 

int hex_to_bytes(unsigned char *binary, const char *hex, size_t len)
{
	for (; len; len--, hex += 2) {
		unsigned int val = (hexval(hex[0]) << 4) | hexval(hex[1]);

		if (val & ~0xff)
			return -1;
		*binary++ = val;
	}
	return 0;
}