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
typedef  size_t uint8_t ;
typedef  size_t ssize_t ;

/* Variables and functions */

__attribute__((used)) static void
rshift_row(uint8_t *buf, size_t len, size_t shift)
{
	ssize_t i, off_byte = shift / 8;
	size_t off_bit = shift % 8;

	if (shift == 0)
		return;
	for (i = len - 1; i >= 0; i--)
		buf[i] = (i >= off_byte ? buf[i - off_byte] >> off_bit : 0) |
		    (i > off_byte ? buf[i - off_byte - 1] << (8 - off_bit) : 0);
}