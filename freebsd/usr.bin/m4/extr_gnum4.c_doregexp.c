#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regmatch_t ;
struct TYPE_7__ {scalar_t__ re_nsub; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  do_regexp (char const*,TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_regexpindex (char const*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_regerror (int,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m4_warnx (char*) ; 
 scalar_t__ mimic_gnu ; 
 int /*<<< orphan*/  pbstr (char const*) ; 
 int regcomp (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  regfree (TYPE_1__*) ; 
 char const* twiddle (char const*) ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 

void
doregexp(const char *argv[], int argc)
{
	int error;
	regex_t re;
	regmatch_t *pmatch;
	const char *source;

	if (argc <= 3) {
		m4_warnx("Too few arguments to regexp");
		return;
	}
	/* special gnu case */
	if (argv[3][0] == '\0' && mimic_gnu) {
		if (argc == 4 || argv[4] == NULL)
			return;
		else
			pbstr(argv[4]);
	}
	source = mimic_gnu ? twiddle(argv[3]) : argv[3];
	error = regcomp(&re, source, REG_EXTENDED|REG_NEWLINE);
	if (error != 0)
		exit_regerror(error, &re, source);

	pmatch = xreallocarray(NULL, re.re_nsub+1, sizeof(regmatch_t), NULL);
	if (argc == 4 || argv[4] == NULL)
		do_regexpindex(argv[2], &re, source, pmatch);
	else
		do_regexp(argv[2], &re, source, argv[4], pmatch);
	free(pmatch);
	regfree(&re);
}