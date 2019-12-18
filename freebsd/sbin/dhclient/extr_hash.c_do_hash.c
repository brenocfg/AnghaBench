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

__attribute__((used)) static int
do_hash(const unsigned char *name, int len, int size)
{
	const unsigned char *s = name;
	int accum = 0, i = len;

	while (i--) {
		/* Add the character in... */
		accum += *s++;
		/* Add carry back in... */
		while (accum > 255)
			accum = (accum & 255) + (accum >> 8);
	}
	return (accum % size);
}