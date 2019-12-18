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
 char* OPTFMT ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* pgm ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	if (debug) /* No need for usage */
		exit(EXIT_FAILURE);

	fprintf(stderr, "Usage: %s [options] bytes:label\n", pgm);
	fprintf(stderr, "       %s [options] -m bytes1:label1 path1 "
	    "[bytes2:label2 path2 ...]\n", pgm);
	fprintf(stderr, "OPTIONS:\n");
#define OPTFMT "\t%-14s %s\n"
	fprintf(stderr, OPTFMT, "-a text",
	    "Append text. Displayed below file progress indicators.");
	fprintf(stderr, OPTFMT, "-b backtitle",
	    "String to be displayed on the backdrop, at top-left.");
	fprintf(stderr, OPTFMT, "-d",
	    "Debug. Write to standard output instead of dialog.");
	fprintf(stderr, OPTFMT, "-D",
	    "Use dialog(1) instead of dialog(3) [default].");
	fprintf(stderr, OPTFMT, "-h",
	    "Produce this output on standard error and exit.");
	fprintf(stderr, OPTFMT, "-i format",
	    "Customize status line format. See fdpv(1) for details.");
	fprintf(stderr, OPTFMT, "-I format",
	    "Customize status line format. See fdpv(1) for details.");
	fprintf(stderr, OPTFMT, "-L size",
	    "Label size. Must be a number greater than 0, or -1.");
	fprintf(stderr, OPTFMT, "-m",
	    "Enable processing of multiple file argiments.");
	fprintf(stderr, OPTFMT, "-n num",
	    "Display at-most num files per screen. Default is -1.");
	fprintf(stderr, OPTFMT, "-N",
	    "No overrun. Stop reading input at stated length, if any.");
	fprintf(stderr, OPTFMT, "-o file",
	    "Output data to file. First %s replaced with label text.");
	fprintf(stderr, OPTFMT, "-p text",
	    "Prefix text. Displayed above file progress indicators.");
	fprintf(stderr, OPTFMT, "-P size",
	    "Mini-progressbar size. Must be a number greater than 3.");
	fprintf(stderr, OPTFMT, "-t title",
	    "Title string to be displayed at top of dialog(1) box.");
	fprintf(stderr, OPTFMT, "-T",
	    "Test mode. Don't actually read any data, but fake it.");
	fprintf(stderr, OPTFMT, "-U num",
	    "Update status line num times per-second. Default is 2.");
	fprintf(stderr, OPTFMT, "-w",
	    "Wide. Width of `-p' and `-a' text bump dialog(1) width.");
	fprintf(stderr, OPTFMT, "-x cmd",
	    "Send data to executed cmd. First %s replaced with label.");
	fprintf(stderr, OPTFMT, "-X",
	    "X11. Use Xdialog(1) instead of dialog(1).");
	exit(EXIT_FAILURE);
}