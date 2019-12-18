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
struct printer {int dummy; } ;

/* Variables and functions */
 int cgetnext (char**,int /*<<< orphan*/ ) ; 
 scalar_t__ firstnextmap (int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_printer (struct printer*) ; 
 int getprintcap_int (char*,struct printer*) ; 
 int /*<<< orphan*/  printcapdb ; 

int
nextprinter(struct printer *pp, int *error)
{
	int status;
	char *bp;

	free_printer(pp);
	status = cgetnext(&bp, printcapdb);
	if (firstnextmap(&status) == 0) {
		if (error)
			*error = status;
		return 0;
	}
	if (error)
		*error = status;
	status = getprintcap_int(bp, pp);
	free(bp);
	if (error && status)
		*error = status;
	return 1;
}