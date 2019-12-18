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
typedef  int wchar_t ;

/* Variables and functions */

__attribute__((used)) static inline int utf8enc_wchar(char *outb, wchar_t c)
{
	if (c <= 0x7F) {
		*outb = c;
		return 1;
	}
	else if (c <= 0x7FF) {
		*outb++ = ((c >>  6) & 0x1F) | 0xC0;
		*outb++ = ( c        & 0x3F) | 0x80;
		return 2;
	}
	else if (c <= 0xFFFF) {
		*outb++ = ((c >> 12) & 0x0F) | 0xE0;
		*outb++ = ((c >>  6) & 0x3F) | 0x80;
		*outb++ = ( c        & 0x3F) | 0x80;
		return 3;
	}
	else if (c <= 0x10FFFF) {
		*outb++ = ((c >> 18) & 0x07) | 0xF0;
		*outb++ = ((c >> 12) & 0x3F) | 0x80;
		*outb++ = ((c >>  6) & 0x3F) | 0x80;
		*outb++ = ( c        & 0x3F) | 0x80;
		return 4;
	}
	else {
		*outb++ = '?';
		return 1;
	}
}