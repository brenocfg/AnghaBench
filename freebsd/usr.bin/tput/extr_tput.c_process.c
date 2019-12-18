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
 int atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char const*,int,char const*) ; 
 int /*<<< orphan*/  outc ; 
 char* tgoto (char*,int,int) ; 
 int /*<<< orphan*/  tputs (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char const*,char,char const*) ; 

__attribute__((used)) static char **
process(const char *cap, char *str, char **argv)
{
	static const char errfew[] =
	    "not enough arguments (%d) for capability `%s'";
	static const char errmany[] =
	    "too many arguments (%d) for capability `%s'";
	static const char erresc[] =
	    "unknown %% escape `%c' for capability `%s'";
	char *cp;
	int arg_need, arg_rows, arg_cols;

	/* Count how many values we need for this capability. */
	for (cp = str, arg_need = 0; *cp != '\0'; cp++)
		if (*cp == '%')
			    switch (*++cp) {
			    case 'd':
			    case '2':
			    case '3':
			    case '.':
			    case '+':
				    arg_need++;
				    break;
			    case '%':
			    case '>':
			    case 'i':
			    case 'r':
			    case 'n':
			    case 'B':
			    case 'D':
				    break;
			    case 'p':
				    if (cp[1]) {
					cp++;
					break;
				    }
			    default:
				/*
				 * hpux has lot's of them, but we complain
				 */
				 warnx(erresc, *cp, cap);
			    }

	/* And print them. */
	switch (arg_need) {
	case 0:
		(void)tputs(str, 1, outc);
		break;
	case 1:
		arg_cols = 0;

		if (*++argv == NULL || *argv[0] == '\0')
			errx(2, errfew, 1, cap);
		arg_rows = atoi(*argv);

		(void)tputs(tgoto(str, arg_cols, arg_rows), 1, outc);
		break;
	case 2:
		if (*++argv == NULL || *argv[0] == '\0')
			errx(2, errfew, 2, cap);
		arg_cols = atoi(*argv);

		if (*++argv == NULL || *argv[0] == '\0')
			errx(2, errfew, 2, cap);
		arg_rows = atoi(*argv);

		(void) tputs(tgoto(str, arg_cols, arg_rows), arg_rows, outc);
		break;

	default:
		errx(2, errmany, arg_need, cap);
	}
	return (argv);
}