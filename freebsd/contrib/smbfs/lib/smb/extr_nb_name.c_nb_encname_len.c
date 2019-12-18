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

int
nb_encname_len(const char *str)
{
	const u_char *cp = (const u_char *)str;
	int len, blen;

	if ((cp[0] & 0xc0) == 0xc0)
		return -1;	/* first two bytes are offset to name */

	len = 1;
	for (;;) {
		blen = *cp;
		if (blen++ == 0)
			break;
		len += blen;
		cp += blen;
	}
	return len;
}