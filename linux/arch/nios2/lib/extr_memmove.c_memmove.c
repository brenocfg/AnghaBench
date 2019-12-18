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

void *memmove(void *d, const void *s, size_t count)
{
	unsigned long dst, src;

	if (!count)
		return d;

	if (d < s) {
		dst = (unsigned long) d;
		src = (unsigned long) s;

		if ((count < 8) || ((dst ^ src) & 3))
			goto restup;

		if (dst & 1) {
			*(char *)dst++ = *(char *)src++;
			count--;
		}
		if (dst & 2) {
			*(short *)dst = *(short *)src;
			src += 2;
			dst += 2;
			count -= 2;
		}
		while (count > 3) {
			*(long *)dst = *(long *)src;
			src += 4;
			dst += 4;
			count -= 4;
		}
restup:
		while (count--)
			*(char *)dst++ = *(char *)src++;
	} else {
		dst = (unsigned long) d + count;
		src = (unsigned long) s + count;

		if ((count < 8) || ((dst ^ src) & 3))
			goto restdown;

		if (dst & 1) {
			src--;
			dst--;
			count--;
			*(char *)dst = *(char *)src;
		}
		if (dst & 2) {
			src -= 2;
			dst -= 2;
			count -= 2;
			*(short *)dst = *(short *)src;
		}
		while (count > 3) {
			src -= 4;
			dst -= 4;
			count -= 4;
			*(long *)dst = *(long *)src;
		}
restdown:
		while (count--) {
			src--;
			dst--;
			*(char *)dst = *(char *)src;
		}
	}

	return d;
}