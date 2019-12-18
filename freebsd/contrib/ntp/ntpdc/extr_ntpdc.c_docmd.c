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
struct xcmd {int* arg; int /*<<< orphan*/  (* handler ) (struct parse*,int /*<<< orphan*/ *) ;} ;
struct parse {char* keyword; scalar_t__ nargs; int /*<<< orphan*/ * argval; } ;

/* Variables and functions */
 int MAXARGS ; 
 scalar_t__ MAXLINE ; 
 int MOREARGS ; 
 int NO ; 
 int NTP_STR ; 
 int OPT ; 
 int /*<<< orphan*/  SETJMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ai_fam_default ; 
 int /*<<< orphan*/  ai_fam_templ ; 
 int /*<<< orphan*/  builtins ; 
 int /*<<< orphan*/ * current_output ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int findcmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xcmd**) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int getarg (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  interrupt_buf ; 
 int jump ; 
 int /*<<< orphan*/  opcmds ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printusage (struct xcmd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct parse*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct parse*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tokenize (char const*,char**,int*) ; 

__attribute__((used)) static void
docmd(
	const char *cmdline
	)
{
	char *tokens[1+MAXARGS+MOREARGS+2];
	struct parse pcmd;
	int ntok;
	int i, ti;
	int rval;
	struct xcmd *xcmd;

	ai_fam_templ = ai_fam_default;
	/*
	 * Tokenize the command line.  If nothing on it, return.
	 */
	if (strlen(cmdline) >= MAXLINE) {
		fprintf(stderr, "***Command ignored, more than %d characters:\n%s\n",
			MAXLINE - 1, cmdline);
		return;
	}
	tokenize(cmdline, tokens, &ntok);
	if (ntok == 0)
	    return;
	
	/*
	 * Find the appropriate command description.
	 */
	i = findcmd(tokens[0], builtins, opcmds, &xcmd);
	if (i == 0) {
		(void) fprintf(stderr, "***Command `%s' unknown\n",
			       tokens[0]);
		return;
	} else if (i >= 2) {
		(void) fprintf(stderr, "***Command `%s' ambiguous\n",
			       tokens[0]);
		return;
	}
	
	/*
	 * Save the keyword, then walk through the arguments, interpreting
	 * as we go.
	 */
	pcmd.keyword = tokens[0];
	pcmd.nargs = 0;
	ti = 1;
	for (i = 0; i < MAXARGS && xcmd->arg[i] != NO;) {
		if ((i+ti) >= ntok) {
			if (!(xcmd->arg[i] & OPT)) {
				printusage(xcmd, stderr);
				return;
			}
			break;
		}
		if ((xcmd->arg[i] & OPT) && (*tokens[i+ti] == '>'))
			break;
		rval = getarg(tokens[i+ti], (int)xcmd->arg[i], &pcmd.argval[i]);
		if (rval == -1) {
			ti++;
			continue;
		}
		if (rval == 0)
			return;
		pcmd.nargs++;
		i++;
	}

	/* Any extra args are assumed to be "OPT|NTP_STR". */
	for ( ; i < MAXARGS + MOREARGS;) {
	     if ((i+ti) >= ntok)
		  break;
		rval = getarg(tokens[i+ti], (int)(OPT|NTP_STR), &pcmd.argval[i]);
		if (rval == -1) {
			ti++;
			continue;
		}
		if (rval == 0)
			return;
		pcmd.nargs++;
		i++;
	}

	i += ti;
	if (i < ntok && *tokens[i] == '>') {
		char *fname;

		if (*(tokens[i]+1) != '\0')
		    fname = tokens[i]+1;
		else if ((i+1) < ntok)
		    fname = tokens[i+1];
		else {
			(void) fprintf(stderr, "***No file for redirect\n");
			return;
		}

		current_output = fopen(fname, "w");
		if (current_output == NULL) {
			(void) fprintf(stderr, "***Error opening %s: ", fname);
			perror("");
			return;
		}
	} else {
		current_output = stdout;
	}

	if (interactive) {
		if ( ! SETJMP(interrupt_buf)) {
			jump = 1;
			(xcmd->handler)(&pcmd, current_output);
			jump = 0;
		} else {
			fflush(current_output);
			fputs("\n >>> command aborted <<<\n", stderr);
			fflush(stderr);
		}
	} else {
		jump = 0;
		(xcmd->handler)(&pcmd, current_output);
	}
	if ((NULL != current_output) && (stdout != current_output)) {
		(void)fclose(current_output);
		current_output = NULL;
	}
}