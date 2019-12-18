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
typedef  scalar_t__ Char ;

/* Variables and functions */

__attribute__((used)) static void
cpy_pad_spaces(Char *dst, Char *src, int width)
{
    int i;

    for (i = 0; i < width; i++) {
	if (*src == (Char) 0)
	    break;
	*dst++ = *src++;
    }

    while (i < width) {
	*dst++ = ' ';
	i++;
    }
    *dst = (Char) 0;
}