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
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t
atol16(const char *p, unsigned char_cnt)
{
	int64_t l;
	int digit;

	l = 0;
	while (char_cnt-- > 0) {
		if (*p >= 'a' && *p <= 'f')
			digit = *p - 'a' + 10;
		else if (*p >= 'A' && *p <= 'F')
			digit = *p - 'A' + 10;
		else if (*p >= '0' && *p <= '9')
			digit = *p - '0';
		else
			return (l);
		p++;
		l <<= 4;
		l |= digit;
	}
	return (l);
}