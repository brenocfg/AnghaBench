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

void
escape(char *p1)
{
	char *p2;

	/* alphabetic escape sequences have to be done in place */
	for (p2 = p1;; p1++, p2++) {
		if (*p1 == '\\') {
			p1++;
			switch(*p1) {
			case '\0':
				*p2 = '\\';
				*++p2 = '\0';
				return;
			case 'a':
			     /* *p2 = '\a'; */
				*p2 = '\007';
				break;
			case 'b':
				*p2 = '\b';
				break;
			case 'f':
				*p2 = '\f';
				break;
			case 'n':
				*p2 = '\n';
				break;
			case 'r':
				*p2 = '\r';
				break;
			case 't':
				*p2 = '\t';
				break;
			case 'v':
				*p2 = '\v';
				break;
			default:
				*p2 = *p1;
				break;
			}
		} else {
			*p2 = *p1;
			if (*p1 == '\0')
				return;
		}
	}
}