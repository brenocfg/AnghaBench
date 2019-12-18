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

__attribute__((used)) static void slow_zero_page(void *page)
{
	int d0, d1;

	__asm__ __volatile__(
		"cld\n\t"
		"rep ; stosl"

			: "=&c" (d0), "=&D" (d1)
			:"a" (0), "1" (page), "0" (1024)
			:"memory");
}