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
 int CMDRTN_ERROR ; 
 int CMDRTN_USAGE ; 
 int ReadFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static int
ReadCmd(int ac, char **av)
{
	FILE *fp;
	int rtn;

	/* Open file */
	switch (ac) {
	case 2:
		if ((fp = fopen(av[1], "r")) == NULL) {
			warn("%s", av[1]);
			return (CMDRTN_ERROR);
		}
		break;
	default:
		return (CMDRTN_USAGE);
	}

	/* Process it */
	rtn = ReadFile(fp);
	fclose(fp);
	return (rtn);
}