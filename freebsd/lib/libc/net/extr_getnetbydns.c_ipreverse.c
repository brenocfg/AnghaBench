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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
ipreverse(char *in, char *out)
{
	char *pos[4];
	int len[4];
	char *p, *start;
	int i = 0;
	int leading = 1;

	/* Fill-in element positions and lengths: pos[], len[]. */
	start = p = in;
	for (;;) {
		if (*p == '.' || *p == '\0') {
			/* Leading 0? */
			if (leading && p - start == 1 && *start == '0')
				len[i] = 0;
			else {
				len[i] = p - start;
				leading = 0;
			}
			pos[i] = start;
			start = p + 1;
			i++;
		}
		if (i == 4)
			break;
		if (*p == 0) {
			for (; i < 4; i++) {
				pos[i] = p;
				len[i] = 0;
			}
			break;
		}
		p++;
	}

	/* Copy the entries in reverse order */
	p = out;
	leading = 1;
	for (i = 3; i >= 0; i--) {
		memcpy(p, pos[i], len[i]);
		if (len[i])
			leading = 0;
		p += len[i];
		/* Need a . separator? */
		if (!leading && i > 0 && len[i - 1])
			*p++ = '.';
	}
	*p = '\0';
}