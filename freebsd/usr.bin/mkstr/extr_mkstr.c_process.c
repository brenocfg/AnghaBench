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
 int EOF ; 
 int /*<<< orphan*/  copystr () ; 
 int getchar () ; 
 scalar_t__ match (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (int) ; 

void
process(void)
{
	int c;

	for (;;) {
		c = getchar();
		if (c == EOF)
			return;
		if (c != 'e') {
			putchar(c);
			continue;
		}
		if (match("error(")) {
			printf("error(");
			c = getchar();
			if (c != '"')
				putchar(c);
			else
				copystr();
		}
	}
}