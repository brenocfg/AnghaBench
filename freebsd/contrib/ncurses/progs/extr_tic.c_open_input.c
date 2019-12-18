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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ExitProgram (int /*<<< orphan*/ ) ; 
 char const* STDIN_NAME ; 
 int S_IFCHR ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int S_IFREG ; 
 char* _nc_progname ; 
 int /*<<< orphan*/ * copy_input (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *
open_input(const char *filename, char *alt_file)
{
    FILE *fp;
    struct stat sb;
    int mode;

    if (!strcmp(filename, "-")) {
	fp = copy_input(stdin, STDIN_NAME, alt_file);
    } else if (stat(filename, &sb) < 0) {
	fprintf(stderr, "%s: %s %s\n", _nc_progname, filename, strerror(errno));
	ExitProgram(EXIT_FAILURE);
    } else if ((mode = (sb.st_mode & S_IFMT)) == S_IFDIR
	       || (mode != S_IFREG && mode != S_IFCHR)) {
	fprintf(stderr, "%s: %s is not a file\n", _nc_progname, filename);
	ExitProgram(EXIT_FAILURE);
    } else {
	fp = fopen(filename, "r");

	if (fp == 0) {
	    fprintf(stderr, "%s: Can't open %s\n", _nc_progname, filename);
	    ExitProgram(EXIT_FAILURE);
	}
	if (mode != S_IFREG) {
	    if (alt_file != 0) {
		FILE *fp2 = copy_input(fp, filename, alt_file);
		fp = fp2;
	    } else {
		fprintf(stderr, "%s: %s is not a file\n", _nc_progname, filename);
		ExitProgram(EXIT_FAILURE);
	    }
	}
    }
    return fp;
}