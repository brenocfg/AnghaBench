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
 int VIS_MIMESTYLE ; 
 int /*<<< orphan*/  printf (char*) ; 

int
foldit(const char *chunk, int col, int max, int flags)
{
	const char *cp;

	/*
	 * Keep track of column position. Insert hidden newline
	 * if this chunk puts us over the limit.
	 */
again:
	cp = chunk;
	while (*cp) {
		switch(*cp) {
		case '\n':
		case '\r':
			col = 0;
			break;
		case '\t':
			col = (col + 8) &~ 07;
			break;
		case '\b':
			col = col ? col - 1 : 0;
			break;
		default:
			col++;
		}
		if (col > (max - 2)) {
			printf(flags & VIS_MIMESTYLE ? "=\n" : "\\\n");
			col = 0;
			goto again;
		} 
		cp++;
	}
	return (col);
}