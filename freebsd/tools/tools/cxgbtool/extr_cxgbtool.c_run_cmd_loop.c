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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  run_cmd (unsigned int,char**,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
run_cmd_loop(int argc, char *argv[], const char *iff_name)
{
	int n;
	unsigned int i;
	char buf[64];
	char *args[8], *s;

	(void) argc;
	args[0] = argv[0];
	args[1] = argv[1];

	/*
	 * Fairly simplistic loop.  Displays a "> " prompt and processes any
	 * input as a cxgbtool command.  You're supposed to enter only the part
	 * after "cxgbtool cxgbX".  Use "quit" or "exit" to exit.  Any error in
	 * the command will also terminate cxgbtool.
	 */
	for (;;) {
		fprintf(stdout, "> ");
		fflush(stdout);
		n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
		if (n <= 0)
			return (0);

		if (buf[--n] != '\n')
			continue;
		else
			buf[n] = 0;

		s = &buf[0];
		for (i = 2; i < sizeof(args)/sizeof(args[0]) - 1; i++) {
			while (s && (*s == ' ' || *s == '\t'))
				s++;
			if ((args[i] = strsep(&s, " \t")) == NULL)
				break;
		}
		args[sizeof(args)/sizeof(args[0]) - 1] = 0;

		if (!strcmp(args[2], "quit") || !strcmp(args[2], "exit"))
			return (0);

		(void) run_cmd(i, args, iff_name);
	}

	/* Can't really get here */
	return (0);
}