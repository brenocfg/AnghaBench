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

__attribute__((used)) static int get_hex_color(const char *in, unsigned char *out)
{
	unsigned int val;
	val = (hexval(in[0]) << 4) | hexval(in[1]);
	if (val & ~0xff)
		return -1;
	*out = val;
	return 0;
}