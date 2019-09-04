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
typedef  size_t uint8_t ;

/* Variables and functions */
 int* utf8proc_utf8class ; 

int git__utf8_charlen(const uint8_t *str, int str_len)
{
	int length, i;

	length = utf8proc_utf8class[str[0]];
	if (!length)
		return -1;

	if (str_len >= 0 && length > str_len)
		return -str_len;

	for (i = 1; i < length; i++) {
		if ((str[i] & 0xC0) != 0x80)
			return -i;
	}

	return length;
}