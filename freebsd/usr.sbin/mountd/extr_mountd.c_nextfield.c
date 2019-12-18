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

__attribute__((used)) static void
nextfield(char **cp, char **endcp)
{
	char *p;
	char quot = 0;

	p = *cp;
	while (*p == ' ' || *p == '\t')
		p++;
	*cp = p;
	while (*p != '\0') {
		if (quot) {
			if (*p == quot)
				quot = 0;
		} else {
			if (*p == '\\' && *(p + 1) != '\0')
				p++;
			else if (*p == '\'' || *p == '"')
				quot = *p;
			else if (*p == ' ' || *p == '\t')
				break;
		}
		p++;
	};
	*endcp = p;
}