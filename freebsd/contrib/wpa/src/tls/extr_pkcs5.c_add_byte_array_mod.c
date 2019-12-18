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
typedef  unsigned int u8 ;

/* Variables and functions */

__attribute__((used)) static void add_byte_array_mod(u8 *a, const u8 *b, size_t len)
{
	size_t i;
	unsigned int carry = 0;

	for (i = len - 1; i < len; i--) {
		carry = carry + a[i] + b[i];
		a[i] = carry & 0xff;
		carry >>= 8;
	}
}