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
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static int
format_256(int64_t v, char *p, int s)
{
	p += s;
	while (s-- > 0) {
		*--p = (char)(v & 0xff);
		v >>= 8;
	}
	*p |= 0x80; /* Set the base-256 marker bit. */
	return (0);
}