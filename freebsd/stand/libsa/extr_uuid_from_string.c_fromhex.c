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
typedef  int uint32_t ;

/* Variables and functions */
 int hex2int (char const) ; 

__attribute__((used)) static uint32_t
fromhex(const char *s, int len, int *ok)
{
	uint32_t v;
	int i, h;

	if (!*ok)
		return 0;
	v = 0;
	for (i = 0; i < len; i++) {
		h = hex2int(s[i]);
		if (h == 16) {
			*ok = 0;
			return v;
		}
		v = (v << 4) | h;
	}
	return v;
}