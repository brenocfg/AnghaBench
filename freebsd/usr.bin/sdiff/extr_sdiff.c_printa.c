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
 int /*<<< orphan*/  enqueue (int /*<<< orphan*/ *,char,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 size_t file2ln ; 
 int /*<<< orphan*/  processq () ; 
 char* xfgets (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
printa(FILE *file, size_t line2)
{
	char *line;

	for (; file2ln <= line2; ++file2ln) {
		if (!(line = xfgets(file)))
			errx(2, "append ended early");
		enqueue(NULL, '>', line);
	}
	processq();
}