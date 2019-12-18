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
 int /*<<< orphan*/  enqueue (char*,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 size_t file1ln ; 
 int /*<<< orphan*/  processq () ; 
 char* xfgets (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
printd(FILE *file1, size_t file1end)
{
	char *line1;

	/* Print out lines file1ln to line2. */
	for (; file1ln <= file1end; ++file1ln) {
		if (!(line1 = xfgets(file1)))
			errx(2, "file1 ended early in delete");
		enqueue(line1, '<', NULL);
	}
	processq();
}