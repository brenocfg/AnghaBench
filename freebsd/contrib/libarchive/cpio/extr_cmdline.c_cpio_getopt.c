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
struct option {char* name; int equivalent; scalar_t__ required; } ;
struct cpio {char* argument; char** argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 struct option* cpio_longopts ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,...) ; 
 char* short_options ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

int
cpio_getopt(struct cpio *cpio)
{
	enum { state_start = 0, state_next_word, state_short, state_long };
	static int state = state_start;
	static char *opt_word;

	const struct option *popt, *match = NULL, *match2 = NULL;
	const char *p, *long_prefix = "--";
	size_t optlength;
	int opt = '?';
	int required = 0;

	cpio->argument = NULL;

	/* First time through, initialize everything. */
	if (state == state_start) {
		/* Skip program name. */
		++cpio->argv;
		--cpio->argc;
		state = state_next_word;
	}

	/*
	 * We're ready to look at the next word in argv.
	 */
	if (state == state_next_word) {
		/* No more arguments, so no more options. */
		if (cpio->argv[0] == NULL)
			return (-1);
		/* Doesn't start with '-', so no more options. */
		if (cpio->argv[0][0] != '-')
			return (-1);
		/* "--" marks end of options; consume it and return. */
		if (strcmp(cpio->argv[0], "--") == 0) {
			++cpio->argv;
			--cpio->argc;
			return (-1);
		}
		/* Get next word for parsing. */
		opt_word = *cpio->argv++;
		--cpio->argc;
		if (opt_word[1] == '-') {
			/* Set up long option parser. */
			state = state_long;
			opt_word += 2; /* Skip leading '--' */
		} else {
			/* Set up short option parser. */
			state = state_short;
			++opt_word;  /* Skip leading '-' */
		}
	}

	/*
	 * We're parsing a group of POSIX-style single-character options.
	 */
	if (state == state_short) {
		/* Peel next option off of a group of short options. */
		opt = *opt_word++;
		if (opt == '\0') {
			/* End of this group; recurse to get next option. */
			state = state_next_word;
			return cpio_getopt(cpio);
		}

		/* Does this option take an argument? */
		p = strchr(short_options, opt);
		if (p == NULL)
			return ('?');
		if (p[1] == ':')
			required = 1;

		/* If it takes an argument, parse that. */
		if (required) {
			/* If arg is run-in, opt_word already points to it. */
			if (opt_word[0] == '\0') {
				/* Otherwise, pick up the next word. */
				opt_word = *cpio->argv;
				if (opt_word == NULL) {
					lafe_warnc(0,
					    "Option -%c requires an argument",
					    opt);
					return ('?');
				}
				++cpio->argv;
				--cpio->argc;
			}
			if (opt == 'W') {
				state = state_long;
				long_prefix = "-W "; /* For clearer errors. */
			} else {
				state = state_next_word;
				cpio->argument = opt_word;
			}
		}
	}

	/* We're reading a long option, including -W long=arg convention. */
	if (state == state_long) {
		/* After this long option, we'll be starting a new word. */
		state = state_next_word;

		/* Option name ends at '=' if there is one. */
		p = strchr(opt_word, '=');
		if (p != NULL) {
			optlength = (size_t)(p - opt_word);
			cpio->argument = (char *)(uintptr_t)(p + 1);
		} else {
			optlength = strlen(opt_word);
		}

		/* Search the table for an unambiguous match. */
		for (popt = cpio_longopts; popt->name != NULL; popt++) {
			/* Short-circuit if first chars don't match. */
			if (popt->name[0] != opt_word[0])
				continue;
			/* If option is a prefix of name in table, record it.*/
			if (strncmp(opt_word, popt->name, optlength) == 0) {
				match2 = match; /* Record up to two matches. */
				match = popt;
				/* If it's an exact match, we're done. */
				if (strlen(popt->name) == optlength) {
					match2 = NULL; /* Forget the others. */
					break;
				}
			}
		}

		/* Fail if there wasn't a unique match. */
		if (match == NULL) {
			lafe_warnc(0,
			    "Option %s%s is not supported",
			    long_prefix, opt_word);
			return ('?');
		}
		if (match2 != NULL) {
			lafe_warnc(0,
			    "Ambiguous option %s%s (matches --%s and --%s)",
			    long_prefix, opt_word, match->name, match2->name);
			return ('?');
		}

		/* We've found a unique match; does it need an argument? */
		if (match->required) {
			/* Argument required: get next word if necessary. */
			if (cpio->argument == NULL) {
				cpio->argument = *cpio->argv;
				if (cpio->argument == NULL) {
					lafe_warnc(0,
					    "Option %s%s requires an argument",
					    long_prefix, match->name);
					return ('?');
				}
				++cpio->argv;
				--cpio->argc;
			}
		} else {
			/* Argument forbidden: fail if there is one. */
			if (cpio->argument != NULL) {
				lafe_warnc(0,
				    "Option %s%s does not allow an argument",
				    long_prefix, match->name);
				return ('?');
			}
		}
		return (match->equivalent);
	}

	return (opt);
}