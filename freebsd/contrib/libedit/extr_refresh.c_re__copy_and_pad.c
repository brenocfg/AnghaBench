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
typedef  char wchar_t ;

/* Variables and functions */

__attribute__((used)) static void
re__copy_and_pad(wchar_t *dst, const wchar_t *src, size_t width)
{
	size_t i;

	for (i = 0; i < width; i++) {
		if (*src == '\0')
			break;
		*dst++ = *src++;
	}

	for (; i < width; i++)
		*dst++ = ' ';

	*dst = '\0';
}