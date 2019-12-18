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
 int DATA_RANGE ; 
 char* basename (char*) ; 
 scalar_t__ execname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void
usage(void)
{
	char *base = (char *)"file_write";
	char *exec = (char *)execname;

	if (exec != NULL)
		exec = strdup(exec);
	if (exec != NULL)
		base = basename(exec);

	(void) printf("Usage: %s [-v] -o {create,overwrite,append} -f file_name"
	    " [-b block_size]\n"
	    "\t[-s offset] [-c write_count] [-d data]\n"
	    "\twhere [data] equal to zero causes chars "
	    "0->%d to be repeated throughout\n", base, DATA_RANGE);

	if (exec) {
		free(exec);
	}

	exit(1);
}