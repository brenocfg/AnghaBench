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
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
pline(int line, int *linep, int *col, int list)
{

	if (list)
		return;

	/*
	 * Print out as many lines as needed to reach parity with the
	 * original input.
	 */

	while (*linep < line) {
		putchar('\n');
		(*linep)++;
	}

	*col = 0;
}