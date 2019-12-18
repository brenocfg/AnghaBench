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
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  putchar (char const) ; 

__attribute__((used)) static void
printcol(const char *s, size_t *col, const size_t col_max)
{

	for (; *s && *col < col_max; ++s) {
		size_t new_col;

		switch (*s) {
		case '\t':
			/*
			 * If rounding to next multiple of eight causes
			 * an integer overflow, just return.
			 */
			if (*col > SIZE_MAX - 8)
				return;

			/* Round to next multiple of eight. */
			new_col = (*col / 8 + 1) * 8;

			/*
			 * If printing the tab goes past the column
			 * width, don't print it and just quit.
			 */
			if (new_col > col_max)
				return;
			*col = new_col;
			break;
		default:
			++(*col);
		}
		putchar(*s);
	}
}