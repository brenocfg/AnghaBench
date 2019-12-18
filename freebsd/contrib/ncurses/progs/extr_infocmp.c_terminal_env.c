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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* _nc_progname ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *
terminal_env(void)
{
    char *terminal;

    if ((terminal = getenv("TERM")) == 0) {
	(void) fprintf(stderr,
		       "%s: environment variable TERM not set\n",
		       _nc_progname);
	exit(EXIT_FAILURE);
    }
    return terminal;
}