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
struct option {char* name; scalar_t__ has_arg; scalar_t__* flag; scalar_t__ val; } ;

/* Variables and functions */
 int BADARG ; 
 int BADCH ; 
#define  DD_PREFIX 130 
#define  D_PREFIX 129 
 int FLAG_LONGONLY ; 
 scalar_t__ PRINT_ERROR ; 
#define  W_PREFIX 128 
 int /*<<< orphan*/  ambig ; 
 int dash_prefix ; 
 int /*<<< orphan*/  illoptstring ; 
 scalar_t__ no_argument ; 
 int /*<<< orphan*/  noarg ; 
 char* optarg ; 
 int /*<<< orphan*/  optind ; 
 scalar_t__ optional_argument ; 
 scalar_t__ optopt ; 
 char* place ; 
 int /*<<< orphan*/  recargstring ; 
 scalar_t__ required_argument ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  warnx (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
parse_long_options(char * const *nargv, const char *options,
	const struct option *long_options, int *idx, int short_too, int flags)
{
	char *current_argv, *has_equal;
#ifdef GNU_COMPATIBLE
	char *current_dash;
#endif
	size_t current_argv_len;
	int i, match, exact_match, second_partial_match;

	current_argv = place;
#ifdef GNU_COMPATIBLE
	switch (dash_prefix) {
		case D_PREFIX:
			current_dash = "-";
			break;
		case DD_PREFIX:
			current_dash = "--";
			break;
		case W_PREFIX:
			current_dash = "-W ";
			break;
		default:
			current_dash = "";
			break;
	}
#endif
	match = -1;
	exact_match = 0;
	second_partial_match = 0;

	optind++;

	if ((has_equal = strchr(current_argv, '=')) != NULL) {
		/* argument found (--option=arg) */
		current_argv_len = has_equal - current_argv;
		has_equal++;
	} else
		current_argv_len = strlen(current_argv);

	for (i = 0; long_options[i].name; i++) {
		/* find matching long option */
		if (strncmp(current_argv, long_options[i].name,
		    current_argv_len))
			continue;

		if (strlen(long_options[i].name) == current_argv_len) {
			/* exact match */
			match = i;
			exact_match = 1;
			break;
		}
		/*
		 * If this is a known short option, don't allow
		 * a partial match of a single character.
		 */
		if (short_too && current_argv_len == 1)
			continue;

		if (match == -1)	/* first partial match */
			match = i;
		else if ((flags & FLAG_LONGONLY) ||
			 long_options[i].has_arg !=
			     long_options[match].has_arg ||
			 long_options[i].flag != long_options[match].flag ||
			 long_options[i].val != long_options[match].val)
			second_partial_match = 1;
	}
	if (!exact_match && second_partial_match) {
		/* ambiguous abbreviation */
		if (PRINT_ERROR)
			warnx(ambig,
#ifdef GNU_COMPATIBLE
			     current_dash,
#endif
			     (int)current_argv_len,
			     current_argv);
		optopt = 0;
		return (BADCH);
	}
	if (match != -1) {		/* option found */
		if (long_options[match].has_arg == no_argument
		    && has_equal) {
			if (PRINT_ERROR)
				warnx(noarg,
#ifdef GNU_COMPATIBLE
				     current_dash,
#endif
				     (int)current_argv_len,
				     current_argv);
			/*
			 * XXX: GNU sets optopt to val regardless of flag
			 */
			if (long_options[match].flag == NULL)
				optopt = long_options[match].val;
			else
				optopt = 0;
#ifdef GNU_COMPATIBLE
			return (BADCH);
#else
			return (BADARG);
#endif
		}
		if (long_options[match].has_arg == required_argument ||
		    long_options[match].has_arg == optional_argument) {
			if (has_equal)
				optarg = has_equal;
			else if (long_options[match].has_arg ==
			    required_argument) {
				/*
				 * optional argument doesn't use next nargv
				 */
				optarg = nargv[optind++];
			}
		}
		if ((long_options[match].has_arg == required_argument)
		    && (optarg == NULL)) {
			/*
			 * Missing argument; leading ':' indicates no error
			 * should be generated.
			 */
			if (PRINT_ERROR)
				warnx(recargstring,
#ifdef GNU_COMPATIBLE
				    current_dash,
#endif
				    current_argv);
			/*
			 * XXX: GNU sets optopt to val regardless of flag
			 */
			if (long_options[match].flag == NULL)
				optopt = long_options[match].val;
			else
				optopt = 0;
			--optind;
			return (BADARG);
		}
	} else {			/* unknown option */
		if (short_too) {
			--optind;
			return (-1);
		}
		if (PRINT_ERROR)
			warnx(illoptstring,
#ifdef GNU_COMPATIBLE
			      current_dash,
#endif
			      current_argv);
		optopt = 0;
		return (BADCH);
	}
	if (idx)
		*idx = match;
	if (long_options[match].flag) {
		*long_options[match].flag = long_options[match].val;
		return (0);
	} else
		return (long_options[match].val);
}