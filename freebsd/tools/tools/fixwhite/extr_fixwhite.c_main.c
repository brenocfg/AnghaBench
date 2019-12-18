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
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  printwhite () ; 
 int readchar () ; 
 int /*<<< orphan*/  savewhite (int,int) ; 
 int /*<<< orphan*/  writechar (char) ; 

int
main(void)
{
	int c;
	bool leading = true;

	while ((c = readchar()) != EOF) {
		if (isspace(c))
			/* Save whitespace. */
			savewhite(c, leading);
		else {
			/* Reprint whitespace and print regular character. */
			printwhite();
			writechar(c);
			leading = false;
		}
	}
	/* Terminate non-empty files with a newline. */
	if (!leading)
		writechar('\n');
	return (0);
}