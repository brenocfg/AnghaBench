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
 scalar_t__ ENOENT ; 
 scalar_t__ ENOEXEC ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hesiod_end (void*) ; 
 int /*<<< orphan*/  hesiod_free_list (void*,char**) ; 
 scalar_t__ hesiod_init (void**) ; 
 char** hesiod_resolve (void*,char*,char*) ; 
 char* hesiod_to_bind (void*,char*,char*) ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int 
main(int argc, char **argv)
{
	char  **list, **p, *bindname, *name, *type;
	int     lflag = 0, errflg = 0, bflag = 0, c;
	void   *context;

	while ((c = getopt(argc, argv, "lb")) != -1) {
		switch (c) {
		case 'l':
			lflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		default:
			errflg++;
			break;
		}
	}
	if (argc - optind != 2 || errflg) {
		fprintf(stderr, "usage: hesinfo [-bl] name type\n");
		fprintf(stderr, "\t-l selects long format\n");
		fprintf(stderr, "\t-b also does hes_to_bind conversion\n");
		exit(2);
	}
	name = argv[optind];
	type = argv[optind + 1];

	if (hesiod_init(&context) < 0) {
		if (errno == ENOEXEC)
			warnx(
			    "hesiod_init: Invalid Hesiod configuration file.");
		else
			warn("hesiod_init");
	}
	/* Display bind name if requested. */
	if (bflag) {
		if (lflag)
			printf("hes_to_bind(%s, %s) expands to\n", name, type);
		bindname = hesiod_to_bind(context, name, type);
		if (!bindname) {
			if (lflag)
				printf("nothing\n");
			if (errno == ENOENT)
				warnx("hesiod_to_bind: Unknown rhs-extension.");
			else
				warn("hesiod_to_bind");
			exit(1);
		}
		printf("%s\n", bindname);
		free(bindname);
		if (lflag)
			printf("which ");
	}
	if (lflag)
		printf("resolves to\n");

	/* Do the hesiod resolve and check for errors. */
	list = hesiod_resolve(context, name, type);
	if (!list) {
		if (lflag)
			printf("nothing\n");
		if (errno == ENOENT)
			warnx("hesiod_resolve: Hesiod name not found.");
		else
			warn("hesiod_resolve");
		exit(1);
	}
	/* Display the results. */
	for (p = list; *p; p++)
		printf("%s\n", *p);

	hesiod_free_list(context, list);
	hesiod_end(context);
	exit(0);
}