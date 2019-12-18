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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ output_sq ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show(const char *arg)
{
	if (output_sq) {
		int sq = '\'', ch;

		putchar(sq);
		while ((ch = *arg++)) {
			if (ch == sq)
				fputs("'\\'", stdout);
			putchar(ch);
		}
		putchar(sq);
		putchar(' ');
	}
	else
		puts(arg);
}