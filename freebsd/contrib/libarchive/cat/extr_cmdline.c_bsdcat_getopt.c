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
struct bsdcat_option {char const* name; int equivalent; scalar_t__ required; } ;
struct bsdcat {char* argument; int getopt_state; char** argv; char* getopt_word; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,...) ; 
 char* short_options ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 struct bsdcat_option* tar_longopts ; 

int
bsdcat_getopt(struct bsdcat *bsdcat)
{
	enum { state_start = 0, state_old_tar, state_next_word,
	       state_short, state_long };

	const struct bsdcat_option *popt, *match = NULL, *match2 = NULL;
	const char *p, *long_prefix = "--";
	size_t optlength;
	int opt = '?';
	int required = 0;

	bsdcat->argument = NULL;

	/* First time through, initialize everything. */
	if (bsdcat->getopt_state == state_start) {
		/* Skip program name. */
		++bsdcat->argv;
		--bsdcat->argc;
		if (*bsdcat->argv == NULL)
			return (-1);
		/* Decide between "new style" and "old style" arguments. */
		bsdcat->getopt_state = state_next_word;
	}

	/*
	 * We're ready to look at the next word in argv.
	 */
	if (bsdcat->getopt_state == state_next_word) {
		/* No more arguments, so no more options. */
		if (bsdcat->argv[0] == NULL)
			return (-1);
		/* Doesn't start with '-', so no more options. */
		if (bsdcat->argv[0][0] != '-')
			return (-1);
		/* "--" marks end of options; consume it and return. */
		if (strcmp(bsdcat->argv[0], "--") == 0) {
			++bsdcat->argv;
			--bsdcat->argc;
			return (-1);
		}
		/* Get next word for parsing. */
		bsdcat->getopt_word = *bsdcat->argv++;
		--bsdcat->argc;
		if (bsdcat->getopt_word[1] == '-') {
			/* Set up long option parser. */
			bsdcat->getopt_state = state_long;
			bsdcat->getopt_word += 2; /* Skip leading '--' */
		} else {
			/* Set up short option parser. */
			bsdcat->getopt_state = state_short;
			++bsdcat->getopt_word;  /* Skip leading '-' */
		}
	}

	/*
	 * We're parsing a group of POSIX-style single-character options.
	 */
	if (bsdcat->getopt_state == state_short) {
		/* Peel next option off of a group of short options. */
		opt = *bsdcat->getopt_word++;
		if (opt == '\0') {
			/* End of this group; recurse to get next option. */
			bsdcat->getopt_state = state_next_word;
			return bsdcat_getopt(bsdcat);
		}

		/* Does this option take an argument? */
		p = strchr(short_options, opt);
		if (p == NULL)
			return ('?');
		if (p[1] == ':')
			required = 1;

		/* If it takes an argument, parse that. */
		if (required) {
			/* If arg is run-in, bsdcat->getopt_word already points to it. */
			if (bsdcat->getopt_word[0] == '\0') {
				/* Otherwise, pick up the next word. */
				bsdcat->getopt_word = *bsdcat->argv;
				if (bsdcat->getopt_word == NULL) {
					lafe_warnc(0,
					    "Option -%c requires an argument",
					    opt);
					return ('?');
				}
				++bsdcat->argv;
				--bsdcat->argc;
			}
			if (opt == 'W') {
				bsdcat->getopt_state = state_long;
				long_prefix = "-W "; /* For clearer errors. */
			} else {
				bsdcat->getopt_state = state_next_word;
				bsdcat->argument = bsdcat->getopt_word;
			}
		}
	}

	/* We're reading a long option, including -W long=arg convention. */
	if (bsdcat->getopt_state == state_long) {
		/* After this long option, we'll be starting a new word. */
		bsdcat->getopt_state = state_next_word;

		/* Option name ends at '=' if there is one. */
		p = strchr(bsdcat->getopt_word, '=');
		if (p != NULL) {
			optlength = (size_t)(p - bsdcat->getopt_word);
			bsdcat->argument = (char *)(uintptr_t)(p + 1);
		} else {
			optlength = strlen(bsdcat->getopt_word);
		}

		/* Search the table for an unambiguous match. */
		for (popt = tar_longopts; popt->name != NULL; popt++) {
			/* Short-circuit if first chars don't match. */
			if (popt->name[0] != bsdcat->getopt_word[0])
				continue;
			/* If option is a prefix of name in table, record it.*/
			if (strncmp(bsdcat->getopt_word, popt->name, optlength) == 0) {
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
			    long_prefix, bsdcat->getopt_word);
			return ('?');
		}
		if (match2 != NULL) {
			lafe_warnc(0,
			    "Ambiguous option %s%s (matches --%s and --%s)",
			    long_prefix, bsdcat->getopt_word, match->name, match2->name);
			return ('?');
		}

		/* We've found a unique match; does it need an argument? */
		if (match->required) {
			/* Argument required: get next word if necessary. */
			if (bsdcat->argument == NULL) {
				bsdcat->argument = *bsdcat->argv;
				if (bsdcat->argument == NULL) {
					lafe_warnc(0,
					    "Option %s%s requires an argument",
					    long_prefix, match->name);
					return ('?');
				}
				++bsdcat->argv;
				--bsdcat->argc;
			}
		} else {
			/* Argument forbidden: fail if there is one. */
			if (bsdcat->argument != NULL) {
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