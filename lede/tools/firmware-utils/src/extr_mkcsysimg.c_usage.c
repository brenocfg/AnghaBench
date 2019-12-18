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
struct board_info {char* model; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 struct board_info* boards ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

void
usage(int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;
	struct board_info *board;

	fprintf(stream, "Usage: %s [OPTIONS...] <file>\n", progname);
	fprintf(stream,
"\n"
"Options:\n"
"  -B <board>      create image for the board specified with <board>.\n"
"                  valid <board> values:\n"
	);
	for (board = boards; board->model != NULL; board++){
		fprintf(stream,
"                  %-12s: %s\n",
		 board->model, board->name);
	};
	fprintf(stream,
"  -d              don't throw error on invalid images\n"
"  -k              keep invalid images\n"
"  -b <file>[:<align>[:<padc>]]\n"
"                  add boot code to the image\n"
"  -c <file>[:<align>[:<padc>]]\n"
"                  add configuration settings to the image\n"
"  -r <file>:[<addr>][:<align>[:<padc>]]\n"
"                  add runtime code to the image\n"
"  -w [<file>:[<addr>][:<align>[:<padc>]]]\n"
"                  add webpages to the image\n"
"  -x <file>[:<align>[:<padc>]]\n"
"                  add extra data at the end of the image\n"
"  -h              show this screen\n"
"Parameters:\n"
"  <file>          write output to the file <file>\n"
	);

	exit(status);
}