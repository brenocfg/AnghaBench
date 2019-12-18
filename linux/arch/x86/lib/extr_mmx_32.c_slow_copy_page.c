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

__attribute__((used)) static void slow_copy_page(void *to, void *from)
{
	int d0, d1, d2;

	__asm__ __volatile__(
		"cld\n\t"
		"rep ; movsl"
		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (1024), "1" ((long) to), "2" ((long) from)
		: "memory");
}