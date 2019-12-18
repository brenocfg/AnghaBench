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
 int /*<<< orphan*/  VIS_CSTYLE ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vis (char*,char,int /*<<< orphan*/ ,char) ; 

void
visdump(char *dp, int datalen, int screenwidth)
{
	int col = 0;
	char *cp;
	int width;
	char visbuf[5];

	printf("       \"");
	col = 8;
	for (;datalen > 0; datalen--, dp++) {
		 vis(visbuf, *dp, VIS_CSTYLE, *(dp+1));
		cp = visbuf;
		/*
		 * Keep track of printables and
		 * space chars (like fold(1)).
		 */
		if (col == 0) {
			putchar('\t');
			col = 8;
		}
		switch(*cp) {
		case '\n':
			col = 0;
			putchar('\n');
			continue;
		case '\t':
			width = 8 - (col&07);
			break;
		default:
			width = strlen(cp);
		}
		if (col + width > (screenwidth-2)) {
			printf("\\\n\t");
			col = 8;
		}
		col += width;
		do {
			putchar(*cp++);
		} while (*cp);
	}
	if (col == 0)
		printf("       ");
	printf("\"\n");
}