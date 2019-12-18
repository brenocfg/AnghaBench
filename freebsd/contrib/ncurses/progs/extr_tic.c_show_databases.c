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
 int /*<<< orphan*/  ExitProgram (int /*<<< orphan*/ ) ; 
 char* _nc_home_terminfo () ; 
 char* _nc_progname ; 
 char* _nc_tic_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* valid_db_path (char const*) ; 

__attribute__((used)) static void
show_databases(const char *outdir)
{
    bool specific = (outdir != 0) || getenv("TERMINFO") != 0;
    char *result;
    const char *tried = 0;

    if (outdir == 0) {
	outdir = _nc_tic_dir(0);
    }
    if ((result = valid_db_path(outdir)) != 0) {
	printf("%s\n", result);
	free(result);
    } else {
	tried = outdir;
    }

    if ((outdir = _nc_home_terminfo())) {
	if ((result = valid_db_path(outdir)) != 0) {
	    printf("%s\n", result);
	    free(result);
	} else if (!specific) {
	    tried = outdir;
	}
    }

    /*
     * If we can write in neither location, give an error message.
     */
    if (tried) {
	fflush(stdout);
	fprintf(stderr, "%s: %s (no permission)\n", _nc_progname, tried);
	ExitProgram(EXIT_FAILURE);
    }
}