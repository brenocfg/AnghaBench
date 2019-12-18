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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int T_ERR ; 
 int T_OK ; 
 int T_PROCESS ; 
 int /*<<< orphan*/  cal_fopen (char*) ; 
 scalar_t__ cal_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * definitions ; 
 int /*<<< orphan*/  sl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sl_find (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * sl_init () ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  trimlr (char**) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
token(char *line, FILE *out, bool *skip)
{
	char *walk, c, a;

	if (strncmp(line, "endif", 5) == 0) {
		*skip = false;
		return (T_OK);
	}

	if (*skip)
		return (T_OK);

	if (strncmp(line, "include", 7) == 0) {
		walk = line + 7;

		trimlr(&walk);

		if (*walk == '\0') {
			warnx("Expecting arguments after #include");
			return (T_ERR);
		}

		if (*walk != '<' && *walk != '\"') {
			warnx("Excecting '<' or '\"' after #include");
			return (T_ERR);
		}

		a = *walk;
		walk++;
		c = walk[strlen(walk) - 1];

		switch(c) {
		case '>':
			if (a != '<') {
				warnx("Unterminated include expecting '\"'");
				return (T_ERR);
			}
			break;
		case '\"':
			if (a != '\"') {
				warnx("Unterminated include expecting '>'");
				return (T_ERR);
			}
			break;
		default:
			warnx("Unterminated include expecting '%c'",
			    a == '<' ? '>' : '\"' );
			return (T_ERR);
		}
		walk[strlen(walk) - 1] = '\0';

		if (cal_parse(cal_fopen(walk), out))
			return (T_ERR);

		return (T_OK);
	}

	if (strncmp(line, "define", 6) == 0) {
		if (definitions == NULL)
			definitions = sl_init();
		walk = line + 6;
		trimlr(&walk);

		if (*walk == '\0') {
			warnx("Expecting arguments after #define");
			return (T_ERR);
		}

		sl_add(definitions, strdup(walk));
		return (T_OK);
	}

	if (strncmp(line, "ifndef", 6) == 0) {
		walk = line + 6;
		trimlr(&walk);

		if (*walk == '\0') {
			warnx("Expecting arguments after #ifndef");
			return (T_ERR);
		}

		if (definitions != NULL && sl_find(definitions, walk) != NULL)
			*skip = true;

		return (T_OK);
	}

	return (T_PROCESS);

}