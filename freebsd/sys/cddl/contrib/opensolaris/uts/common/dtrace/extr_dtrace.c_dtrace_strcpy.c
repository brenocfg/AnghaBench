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
typedef  char uint8_t ;

/* Variables and functions */
 char dtrace_load8 (uintptr_t) ; 

__attribute__((used)) static void
dtrace_strcpy(const void *src, void *dst, size_t len)
{
	if (len != 0) {
		uint8_t *s1 = dst, c;
		const uint8_t *s2 = src;

		do {
			*s1++ = c = dtrace_load8((uintptr_t)s2++);
		} while (--len != 0 && c != '\0');
	}
}