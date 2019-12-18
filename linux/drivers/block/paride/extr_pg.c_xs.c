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

__attribute__((used)) static void xs(char *buf, char *targ, int len)
{
	char l = '\0';
	int k;

	for (k = 0; k < len; k++) {
		char c = *buf++;
		if (c != ' ' && c != l)
			l = *targ++ = c;
	}
	if (l == ' ')
		targ--;
	*targ = '\0';
}