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
 unsigned int inb (unsigned long) ; 

void insb (unsigned long port, void *dst, unsigned long count)
{
	unsigned char *p;

	p = (unsigned char *)dst;

	while (((unsigned long)p) & 0x3) {
		if (!count)
			return;
		count--;
		*p = inb(port);
		p++;
	}

	while (count >= 4) {
		unsigned int w;
		count -= 4;
		w = inb(port) << 24;
		w |= inb(port) << 16;
		w |= inb(port) << 8;
		w |= inb(port);
		*(unsigned int *) p = w;
		p += 4;
	}

	while (count) {
		--count;
		*p = inb(port);
		p++;
	}
}