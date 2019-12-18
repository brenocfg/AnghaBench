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
typedef  int uint32_t ;

/* Variables and functions */

int
l64a_r(long value, char *buffer, int buflen)
{
	static const char chars[] =
	    "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	uint32_t v;

	v = value;
	while (buflen-- > 0) {
		if (v == 0) {
			*buffer = '\0';
			return (0);
		}
		*buffer++ = chars[v & 0x3f];
		v >>= 6;
	}
	return (-1);
}