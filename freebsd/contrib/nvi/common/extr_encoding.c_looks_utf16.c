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
typedef  int u_char ;

/* Variables and functions */
 scalar_t__ T ; 
 scalar_t__* text_chars ; 

int
looks_utf16(const char *ibuf, size_t nbytes)
{
	const u_char *buf = (u_char *)ibuf;
	int bigend;
	size_t i;
	unsigned int c;
	int bom;
	int following = 0;

	if (nbytes < 2)
		return 0;

	bom = buf[0] << 8 ^ buf[1];
	if (bom == 0xFFFE)
		bigend = 0;
	else if (bom == 0xFEFF)
		bigend = 1;
	else
		return 0;

	for (i = 2; i + 1 < nbytes; i += 2) {
		if (bigend)
			c = buf[i] << 8 ^ buf[i + 1];
		else
			c = buf[i] ^ buf[i + 1] << 8;

		if (!following)
			if (c < 0xD800 || c > 0xDFFF)
				if (c < 128 && text_chars[c] != T)
					return 0;
				else
					following = 0;
			else if (c > 0xDBFF)
				return 0;
			else {
				following = 1;
				continue;
			}
		else if (c < 0xDC00 || c > 0xDFFF)
			return 0;
	}

	return 1 + bigend;
}