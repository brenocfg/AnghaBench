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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char HEX (int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

void xdump(FILE * file, char *msg, void *p, int size)
{
#define HEX(x)  ((x) < 10 ? '0' + (x) : 'a' + ((x) -10))
	uint8_t *cp = p;
	int i;

	if (msg)
		fputs(msg, file);

	for (i = 0; i < size;) {
		fputc(HEX(*cp >> 4), file);
		fputc(HEX(*cp & 0xf), file);
		if (++i >= size)
			break;
		fputc(HEX(cp[1] >> 4), file);
		fputc(HEX(cp[1] & 0xf), file);
		if ((++i) % 16)
			fputc(' ', file);
		else
			fputc('\n', file);
		cp += 2;
	}
	if (i % 16)
		fputc('\n', file);
}