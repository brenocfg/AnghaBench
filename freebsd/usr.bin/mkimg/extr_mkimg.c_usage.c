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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  print_formats (int) ; 
 int /*<<< orphan*/  print_schemes (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
usage(const char *why)
{

	warnx("error: %s", why);
	fputc('\n', stderr);
	fprintf(stderr, "usage: %s <options>\n", getprogname());

	fprintf(stderr, "    options:\n");
	fprintf(stderr, "\t--formats\t-  list image formats\n");
	fprintf(stderr, "\t--schemes\t-  list partition schemes\n");
	fprintf(stderr, "\t--version\t-  show version information\n");
	fputc('\n', stderr);
	fprintf(stderr, "\t-a <num>\t-  mark num'th partion as active\n");
	fprintf(stderr, "\t-b <file>\t-  file containing boot code\n");
	fprintf(stderr, "\t-c <num>\t-  minimum capacity (in bytes) of the disk\n");
	fprintf(stderr, "\t-C <num>\t-  maximum capacity (in bytes) of the disk\n");
	fprintf(stderr, "\t-f <format>\n");
	fprintf(stderr, "\t-o <file>\t-  file to write image into\n");
	fprintf(stderr, "\t-p <partition>\n");
	fprintf(stderr, "\t-s <scheme>\n");
	fprintf(stderr, "\t-v\t\t-  increase verbosity\n");
	fprintf(stderr, "\t-y\t\t-  [developers] enable unit test\n");
	fprintf(stderr, "\t-H <num>\t-  number of heads to simulate\n");
	fprintf(stderr, "\t-P <num>\t-  physical sector size\n");
	fprintf(stderr, "\t-S <num>\t-  logical sector size\n");
	fprintf(stderr, "\t-T <num>\t-  number of tracks to simulate\n");
	fputc('\n', stderr);
	print_formats(1);
	fputc('\n', stderr);
	print_schemes(1);
	fputc('\n', stderr);
	fprintf(stderr, "    partition specification:\n");
	fprintf(stderr, "\t<t>[/<l>]::<size>[:[+]<offset>]\t-  "
	    "empty partition of given size and\n\t\t\t\t\t"
	    "   optional relative or absolute offset\n");
	fprintf(stderr, "\t<t>[/<l>]:=<file>\t\t-  partition content and size "
	    "are\n\t\t\t\t\t   determined by the named file\n");
	fprintf(stderr, "\t<t>[/<l>]:-<cmd>\t\t-  partition content and size "
	    "are taken\n\t\t\t\t\t   from the output of the command to run\n");
	fprintf(stderr, "\t-\t\t\t\t-  unused partition entry\n");
	fprintf(stderr, "\t    where:\n");
	fprintf(stderr, "\t\t<t>\t-  scheme neutral partition type\n");
	fprintf(stderr, "\t\t<l>\t-  optional scheme-dependent partition "
	    "label\n");

	exit(EX_USAGE);
}