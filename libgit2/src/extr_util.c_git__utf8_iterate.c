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
typedef  int uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int git__utf8_charlen (int const*,int) ; 

int git__utf8_iterate(const uint8_t *str, int str_len, int32_t *dst)
{
	int length;
	int32_t uc = -1;

	*dst = -1;
	length = git__utf8_charlen(str, str_len);
	if (length < 0)
		return -1;

	switch (length) {
		case 1:
			uc = str[0];
			break;
		case 2:
			uc = ((str[0] & 0x1F) <<  6) + (str[1] & 0x3F);
			if (uc < 0x80) uc = -1;
			break;
		case 3:
			uc = ((str[0] & 0x0F) << 12) + ((str[1] & 0x3F) <<  6)
				+ (str[2] & 0x3F);
			if (uc < 0x800 || (uc >= 0xD800 && uc < 0xE000) ||
					(uc >= 0xFDD0 && uc < 0xFDF0)) uc = -1;
			break;
		case 4:
			uc = ((str[0] & 0x07) << 18) + ((str[1] & 0x3F) << 12)
				+ ((str[2] & 0x3F) <<  6) + (str[3] & 0x3F);
			if (uc < 0x10000 || uc >= 0x110000) uc = -1;
			break;
	}

	if (uc < 0 || ((uc & 0xFFFF) >= 0xFFFE))
		return -1;

	*dst = uc;
	return length;
}