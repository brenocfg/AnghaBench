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

/* Variables and functions */

void strexpandnl(char *source)
{
	uint8_t backslash = 0;
	char *cp1;
	char *cp2;
	
	/* Replace '\n' with literal in dprompt */
	cp1 = cp2 = source;
	while (*cp2 != '\0') {
		*cp1 = *cp2;
		if (*cp2 == '\\')
			backslash++;
		else if (*cp2 != 'n')
			backslash = 0;
		else if (backslash > 0) {
			*(--cp1) = (backslash & 1) == 1 ? '\n' : 'n';
			backslash = 0;
		}
		cp1++;
		cp2++;
	}
	*cp1 = *cp2;
}