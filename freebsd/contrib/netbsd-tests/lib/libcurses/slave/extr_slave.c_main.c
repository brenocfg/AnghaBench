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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/ * cmdpipe ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/ * initscr () ; 
 int /*<<< orphan*/  process_commands (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * slvpipe ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	WINDOW *mainscr;

	if (argc != 5) {
		fprintf(stderr, "Usage: %s <cmdin> <cmdout> <slvin> slvout>\n",
			getprogname());
		return 0;
	}
	sscanf(argv[1], "%d", &cmdpipe[0]);
	sscanf(argv[2], "%d", &cmdpipe[1]);
	sscanf(argv[3], "%d", &slvpipe[0]);
	sscanf(argv[4], "%d", &slvpipe[1]);

	mainscr = initscr();
	if (mainscr == NULL)
		err(1, "initscr failed");

	process_commands(mainscr);

	return 0;
}