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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int MAX_ARGS ; 
 int errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int run_cmd (int,char const**) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
run_cmd_loop(void)
{
	int i, rc = 0;
	char buffer[128], *buf;
	const char *args[MAX_ARGS + 1];

	/*
	 * Simple loop: displays a "> " prompt and processes any input as a
	 * cxgbetool command.  You're supposed to enter only the part after
	 * "cxgbetool t4nexX".  Use "quit" or "exit" to exit.
	 */
	for (;;) {
		fprintf(stdout, "> ");
		fflush(stdout);
		buf = fgets(buffer, sizeof(buffer), stdin);
		if (buf == NULL) {
			if (ferror(stdin)) {
				warn("stdin error");
				rc = errno;	/* errno from fgets */
			}
			break;
		}

		i = 0;
		while ((args[i] = strsep(&buf, " \t\n")) != NULL) {
			if (args[i][0] != 0 && ++i == MAX_ARGS)
				break;
		}
		args[i] = 0;

		if (i == 0)
			continue;	/* skip empty line */

		if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
			break;

		rc = run_cmd(i, args);
	}

	/* rc normally comes from the last command (not including quit/exit) */
	return (rc);
}