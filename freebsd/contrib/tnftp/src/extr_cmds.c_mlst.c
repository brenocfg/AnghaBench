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
 int /*<<< orphan*/  COMMAND_1ARG (int,char**,char*) ; 
 size_t FEAT_MLST ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/ * features ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ttyout ; 
 int verbose ; 

void
mlst(int argc, char *argv[])
{
	int oldverbose = verbose;

	if (argc < 1 || argc > 2) {
		UPRINTF("usage: %s [remote-path]\n", argv[0]);
		code = -1;
		return;
	}
	if (! features[FEAT_MLST]) {
		fprintf(ttyout,
		    "MLST is not supported by the remote server.\n");
		return;
	}
	verbose = 1;	/* If we aren't verbose, this doesn't do anything! */
	COMMAND_1ARG(argc, argv, "MLST");
	verbose = oldverbose;
}