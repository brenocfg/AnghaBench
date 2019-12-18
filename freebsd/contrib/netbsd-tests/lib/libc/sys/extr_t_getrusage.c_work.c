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
 int UINT16_MAX ; 

__attribute__((used)) static void
work(void)
{
	size_t n = UINT16_MAX * 10;

	while (n > 0) {
#ifdef __or1k__
		 asm volatile("l.nop");	/* Do something. */
#elif defined(__ia64__)
		 asm volatile("nop 0"); /* Do something. */
#else
		 asm volatile("nop");	/* Do something. */
#endif
		 n--;
	}
}