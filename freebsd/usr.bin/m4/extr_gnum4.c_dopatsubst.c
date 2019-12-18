#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regmatch_t ;
struct TYPE_6__ {scalar_t__ re_nsub; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  addchar (char const) ; 
 int /*<<< orphan*/  addchars (char const*,size_t) ; 
 int /*<<< orphan*/  do_subst (char const*,TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_regerror (int,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getstring () ; 
 int /*<<< orphan*/  m4_warnx (char*) ; 
 scalar_t__ mimic_gnu ; 
 int /*<<< orphan*/  pbstr (int /*<<< orphan*/ ) ; 
 int regcomp (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  regfree (TYPE_1__*) ; 
 size_t strlen (char const*) ; 
 char const* twiddle (char const*) ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 

void
dopatsubst(const char *argv[], int argc)
{
	if (argc <= 3) {
		m4_warnx("Too few arguments to patsubst");
		return;
	}
	/* special case: empty regexp */
	if (argv[3][0] == '\0') {
		const char *s;
		size_t len;
		if (argc > 4 && argv[4])
			len = strlen(argv[4]);
		else
			len = 0;
		for (s = argv[2]; *s != '\0'; s++) {
			addchars(argv[4], len);
			addchar(*s);
		}
	} else {
		int error;
		regex_t re;
		regmatch_t *pmatch;
		int mode = REG_EXTENDED;
		const char *source;
		size_t l = strlen(argv[3]);

		if (!mimic_gnu ||
		    (argv[3][0] == '^') ||
		    (l > 0 && argv[3][l-1] == '$'))
			mode |= REG_NEWLINE;

		source = mimic_gnu ? twiddle(argv[3]) : argv[3];
		error = regcomp(&re, source, mode);
		if (error != 0)
			exit_regerror(error, &re, source);

		pmatch = xreallocarray(NULL, re.re_nsub+1, sizeof(regmatch_t),
		    NULL);
		do_subst(argv[2], &re, source,
		    argc > 4 && argv[4] != NULL ? argv[4] : "", pmatch);
		free(pmatch);
		regfree(&re);
	}
	pbstr(getstring());
}