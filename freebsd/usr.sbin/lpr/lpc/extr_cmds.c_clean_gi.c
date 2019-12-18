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
 scalar_t__ cln_debug ; 
 scalar_t__ cln_filecnt ; 
 double cln_minage ; 
 int /*<<< orphan*/  cln_now ; 
 scalar_t__ cln_queuecnt ; 
 scalar_t__ cln_sizecnt ; 
 scalar_t__ cln_testonly ; 
 int generic_initerr ; 
 char* generic_nullarg ; 
 int /*<<< orphan*/ * generic_wrapup ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrapup_clean ; 

void
clean_gi(int argc, char *argv[])
{

	/* init some fields before 'clean' is called for each queue */
	cln_queuecnt = 0;
	cln_now = time(NULL);
	cln_minage = 3600.0;		/* only delete files >1h old */
	cln_filecnt = 0;
	cln_sizecnt = 0;
	cln_debug = 0;
	cln_testonly = 0;
	generic_wrapup = &wrapup_clean;

	/* see if there are any options specified before the ptr list */
	for (; argc > 0; argc--, argv++) {
		if (**argv != '-')
			break;
		if (strcmp(*argv, "-d") == 0) {
			/* just an example of an option... */
			cln_debug++;
			*argv = generic_nullarg;	/* "erase" it */
		} else {
			printf("Invalid option '%s'\n", *argv);
			generic_initerr = 1;
		}
	}

	return;
}