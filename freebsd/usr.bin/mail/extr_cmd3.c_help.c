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
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _PATH_HELP ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

int
help(void)
{
	int c;
	FILE *f;

	if ((f = Fopen(_PATH_HELP, "r")) == NULL) {
		warn("%s", _PATH_HELP);
		return (1);
	}
	while ((c = getc(f)) != EOF)
		putchar(c);
	(void)Fclose(f);
	return (0);
}