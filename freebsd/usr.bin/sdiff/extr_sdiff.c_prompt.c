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
 int eparse (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  int_usage () ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  outfp ; 
 int /*<<< orphan*/  putchar (char) ; 
 int sflag ; 
 int /*<<< orphan*/  stdin ; 
 char* xfgets (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prompt(const char *s1, const char *s2)
{
	char *cmd;

	/* Print command prompt. */
	putchar('%');

	/* Get user input. */
	for (; (cmd = xfgets(stdin)); free(cmd)) {
		const char *p;

		/* Skip leading whitespace. */
		for (p = cmd; isspace(*p); ++p)
			;
		switch (*p) {
		case 'e':
			/* Skip `e'. */
			++p;
			if (eparse(p, s1, s2) == -1)
				goto USAGE;
			break;
		case 'l':
		case '1':
			/* Choose left column as-is. */
			if (s1 != NULL)
				fprintf(outfp, "%s\n", s1);
			/* End of command parsing. */
			break;
		case 'q':
			goto QUIT;
		case 'r':
		case '2':
			/* Choose right column as-is. */
			if (s2 != NULL)
				fprintf(outfp, "%s\n", s2);
			/* End of command parsing. */
			break;
		case 's':
			sflag = 1;
			goto PROMPT;
		case 'v':
			sflag = 0;
			/* FALLTHROUGH */
		default:
			/* Interactive usage help. */
USAGE:
			int_usage();
PROMPT:
			putchar('%');

			/* Prompt user again. */
			continue;
		}
		free(cmd);
		return;
	}

	/*
	 * If there was no error, we received an EOF from stdin, so we
	 * should quit.
	 */
QUIT:
	fclose(outfp);
	exit(0);
}