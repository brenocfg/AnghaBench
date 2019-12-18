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
typedef  int register_t ;

/* Variables and functions */
 int cacheline_size ; 

void
__syncicache(void *from, int len)
{
	register_t l, off;
	char	*p;

	off = (uintptr_t)from & (cacheline_size - 1);
	l = len += off;
	p = (char *)from - off;

	do {
		__asm __volatile ("dcbst 0,%0" :: "r"(p));
		p += cacheline_size;
	} while ((l -= cacheline_size) > 0);
	__asm __volatile ("sync");
	p = (char *)from - off;
	do {
		__asm __volatile ("icbi 0,%0" :: "r"(p));
		p += cacheline_size;
	} while ((len -= cacheline_size) > 0);
	__asm __volatile ("sync; isync");
}