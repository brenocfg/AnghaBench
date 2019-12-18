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
struct xcmd {char* keyword; int* arg; char** desc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXARGS ; 
 int NO ; 
 int OPT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
printusage(
	struct xcmd *xcp,
	FILE *fp
	)
{
	register int i;

	/* XXX: Do we need to warn about extra args here too? */

	(void) fprintf(fp, "usage: %s", xcp->keyword);
	for (i = 0; i < MAXARGS && xcp->arg[i] != NO; i++) {
		if (xcp->arg[i] & OPT)
		    (void) fprintf(fp, " [ %s ]", xcp->desc[i]);
		else
		    (void) fprintf(fp, " %s", xcp->desc[i]);
	}
	(void) fprintf(fp, "\n");
}