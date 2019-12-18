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
struct getentdb {int /*<<< orphan*/  (* callback ) (int,char**) ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int RV_USAGE ; 
 struct getentdb* databases ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct getentdb	*curdb;

	setprogname(argv[0]);

	if (argc < 2)
		usage();
	for (curdb = databases; curdb->name != NULL; curdb++) {
		if (strcmp(curdb->name, argv[1]) == 0) {
			exit(curdb->callback(argc, argv));
		}
	}
	fprintf(stderr, "Unknown database: %s\n", argv[1]);
	usage();
	/* NOTREACHED */
	return RV_USAGE;
}