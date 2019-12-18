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
 int fscanf (int /*<<< orphan*/ *,char*,unsigned long*) ; 
 int /*<<< orphan*/  logit (char*,char*,...) ; 

__attribute__((used)) static unsigned long
read_checkpoint(char *cpfile)
{
	FILE *fp;
	unsigned long lineno = 0;

	if ((fp = fopen(cpfile, "r")) == NULL)
		return 0;
	if (fscanf(fp, "%lu\n", &lineno) < 1)
		logit("Failed to load checkpoint from '%s'", cpfile);
	else
		logit("Loaded checkpoint from '%s' line %lu", cpfile, lineno);
	fclose(fp);
	return lineno;
}