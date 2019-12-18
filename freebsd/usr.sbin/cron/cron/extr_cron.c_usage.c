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
 char** DebugFlagNames ; 
 int /*<<< orphan*/  ERROR_EXIT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage() {
#if DEBUGGING
    char **dflags;
#endif

	fprintf(stderr, "usage: cron [-j jitter] [-J rootjitter] "
			"[-m mailto] [-n] [-s] [-o] [-x debugflag[,...]]\n");
#if DEBUGGING
	fprintf(stderr, "\ndebugflags: ");

        for(dflags = DebugFlagNames; *dflags; dflags++) {
		fprintf(stderr, "%s ", *dflags);
	}
        fprintf(stderr, "\n");
#endif

	exit(ERROR_EXIT);
}