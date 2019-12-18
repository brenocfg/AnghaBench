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
 int /*<<< orphan*/  PATH_MOUNTTAB ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,long,char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
add_mtab(char *hostp, char *dirp)
{
	FILE *mtabfile;

	if ((mtabfile = fopen(PATH_MOUNTTAB, "a")) == NULL)
		return (0);
	else {
		fprintf(mtabfile, "%ld\t%s\t%s\n",
		    (long)time(NULL), hostp, dirp);
		fclose(mtabfile);
		return (1);
	}
}