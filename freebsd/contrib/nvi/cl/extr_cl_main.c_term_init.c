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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  setupterm (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
term_init(char *name, char *ttype)
{
	int err;

	/* Set up the terminal database information. */
	setupterm(ttype, STDOUT_FILENO, &err);
	switch (err) {
	case -1:
		(void)fprintf(stderr,
		    "%s: No terminal database found\n", name);
		exit (1);
	case 0:
		(void)fprintf(stderr,
		    "%s: %s: unknown terminal type\n", name, ttype);
		exit (1);
	}
}