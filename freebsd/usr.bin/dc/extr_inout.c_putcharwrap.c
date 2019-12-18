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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MAX_CHARS_PER_LINE ; 
 scalar_t__ charcount ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int lastchar ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
putcharwrap(FILE *f, int ch)
{

	if (charcount >= MAX_CHARS_PER_LINE) {
		charcount = 0;
		fputs("\\\n", f);
	}
	if (lastchar != -1) {
		charcount++;
		putc(lastchar, f);
	}
	lastchar = ch;
}