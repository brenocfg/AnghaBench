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
 int /*<<< orphan*/  command (char*,char*,...) ; 
 int /*<<< orphan*/ * features ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ttyout ; 
 int verbose ; 

void
opts(int argc, char *argv[])
{
	int oldverbose = verbose;

	if (argc < 2 || argc > 3) {
		UPRINTF("usage: %s command [options]\n", argv[0]);
		code = -1;
		return;
	}
	if (! features[FEAT_FEAT]) {
		fprintf(ttyout,
		    "OPTS is not supported by the remote server.\n");
		return;
	}
	verbose = 1;	/* If we aren't verbose, this doesn't do anything! */
	if (argc == 2)
		command("OPTS %s", argv[1]);
	else
		command("OPTS %s %s", argv[1], argv[2]);
	verbose = oldverbose;
}