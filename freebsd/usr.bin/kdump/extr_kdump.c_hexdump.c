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
 int /*<<< orphan*/  printf (char*,...) ; 

void
hexdump(char *p, int len, int screenwidth)
{
	int n, i;
	int width;

	width = 0;
	do {
		width += 2;
		i = 13;			/* base offset */
		i += (width / 2) + 1;	/* spaces every second byte */
		i += (width * 2);	/* width of bytes */
		i += 3;			/* "  |" */
		i += width;		/* each byte */
		i += 1;			/* "|" */
	} while (i < screenwidth);
	width -= 2;

	for (n = 0; n < len; n += width) {
		for (i = n; i < n + width; i++) {
			if ((i % width) == 0) {	/* beginning of line */
				printf("       0x%04x", i);
			}
			if ((i % 2) == 0) {
				printf(" ");
			}
			if (i < len)
				printf("%02x", p[i] & 0xff);
			else
				printf("  ");
		}
		printf("  |");
		for (i = n; i < n + width; i++) {
			if (i >= len)
				break;
			if (p[i] >= ' ' && p[i] <= '~')
				printf("%c", p[i]);
			else
				printf(".");
		}
		printf("|\n");
	}
	if ((i % width) != 0)
		printf("\n");
}