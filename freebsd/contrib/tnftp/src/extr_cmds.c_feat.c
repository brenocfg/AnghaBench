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
 size_t FEAT_FEAT ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  command (char*) ; 
 int /*<<< orphan*/ * features ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ttyout ; 
 int verbose ; 

void
feat(int argc, char *argv[])
{
	int oldverbose = verbose;

	if (argc == 0) {
		UPRINTF("usage: %s\n", argv[0]);
		code = -1;
		return;
	}
	if (! features[FEAT_FEAT]) {
		fprintf(ttyout,
		    "FEAT is not supported by the remote server.\n");
		return;
	}
	verbose = 1;	/* If we aren't verbose, this doesn't do anything! */
	(void)command("FEAT");
	verbose = oldverbose;
}