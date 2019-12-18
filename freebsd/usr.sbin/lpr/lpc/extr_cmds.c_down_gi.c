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
 int /*<<< orphan*/ * args2line (int,char**) ; 
 int /*<<< orphan*/ * generic_msg ; 
 char* generic_nullarg ; 
 int /*<<< orphan*/ * strdup (char*) ; 

void
down_gi(int argc, char *argv[])
{

	/* If `-msg' was specified, then this routine has nothing to do. */
	if (generic_msg != NULL)
		return;

	/*
	 * If the user only gave one parameter, then use a default msg.
	 * (if argc == 1 at this point, then *argv == name of printer).
	 */ 
	if (argc == 1) {
		generic_msg = strdup("printing disabled\n");
		return;
	}

	/*
	 * The user specified multiple parameters, and did not specify
	 * `-msg'.  Build a message from all the parameters after the
	 * first one (and nullify those parameters so generic-processing
	 * will not process them as printer-queue names).
	 */
	argc--;
	argv++;
	generic_msg = args2line(argc, argv);
	for (; argc > 0; argc--, argv++)
		*argv = generic_nullarg;	/* "erase" it */
}