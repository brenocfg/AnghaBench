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
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */

void
cpy8to16(const char *src, CHAR16 *dst, size_t len)
{
	len <<= 1;		/* Assume CHAR16 is 2 bytes */
	while (len > 0 && *src) {
		*dst++ = *src++;
		len--;
	}
	*dst++ = (CHAR16)0;
}