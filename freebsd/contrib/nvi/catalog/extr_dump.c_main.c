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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  parse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
main(int argc, char *argv[])
{
	FILE *fp;

	for (; *argv != NULL; ++argv) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			return (1);
		}
		parse(fp);
		(void)fclose(fp);
	}
	return (0);
}