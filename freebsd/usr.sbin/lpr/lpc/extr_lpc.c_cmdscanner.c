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
struct cmd {int c_opts; int /*<<< orphan*/  (* c_handler ) (scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * c_generic; } ;
typedef  int /*<<< orphan*/  History ;
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 int LPC_PRIVCMD ; 
 int /*<<< orphan*/  LPR_OPER ; 
 scalar_t__ MAX_CMDLINE ; 
 size_t MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  cgetset (int /*<<< orphan*/ *) ; 
 scalar_t__* cmdline ; 
 char* el_gets (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * el_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int el_parse (int /*<<< orphan*/ *,scalar_t__,char const**) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 int /*<<< orphan*/  generic (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (scalar_t__,int /*<<< orphan*/ *),scalar_t__,int /*<<< orphan*/ *) ; 
 struct cmd* getcmd (int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * history_init () ; 
 scalar_t__ ingroup (int /*<<< orphan*/ ) ; 
 int lpc_prompt ; 
 int /*<<< orphan*/  makeargv () ; 
 scalar_t__ margc ; 
 int /*<<< orphan*/ * margv ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  quit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cmdscanner(void)
{
	register struct cmd *c;
	static EditLine *el;
	static History *hist;
	HistEvent he;
	size_t len;
	int num;
	const char *bp;

	num = 0;
	bp = NULL;
	el = NULL;
	hist = NULL;
	for (;;) {
		if (fromatty) {
			if (!el) {
				el = el_init("lpc", stdin, stdout, stderr);
				hist = history_init();
				history(hist, &he, H_SETSIZE, 100);
				el_set(el, EL_HIST, history, hist);
				el_set(el, EL_EDITOR, "emacs");
				el_set(el, EL_PROMPT, lpc_prompt);
				el_set(el, EL_SIGNAL, 1);
				el_source(el, NULL);
				/*
				 * EditLine init may call 'cgetset()' to set a
				 * capability-db meant for termcap (eg: to set
				 * terminal type 'xterm').  Reset that now, or
				 * that same db-information will be used for
				 * printcap (giving us an "xterm" printer, with
				 * all kinds of invalid capabilities...).
				 */
				cgetset(NULL);
			}
			if ((bp = el_gets(el, &num)) == NULL || num == 0)
				quit(0, NULL);

			len = MIN(MAX_CMDLINE - 1, num);
			memcpy(cmdline, bp, len);
			cmdline[len] = 0; 
			history(hist, &he, H_ENTER, bp);

		} else {
			if (fgets(cmdline, MAX_CMDLINE, stdin) == NULL)
				quit(0, NULL);
			if (cmdline[0] == 0 || cmdline[0] == '\n')
				break;
		}

		makeargv();
		if (margc == 0)
			continue;
		if (el != NULL && el_parse(el, margc, (const char **)margv) != -1)
			continue;

		c = getcmd(margv[0]);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == NULL) {
			printf("?Invalid command\n");
			continue;
		}
		if ((c->c_opts & LPC_PRIVCMD) && getuid() &&
		    ingroup(LPR_OPER) == 0) {
			printf("?Privileged command\n");
			continue;
		}

		/*
		 * Two different commands might have the same generic rtn
		 * (eg: "clean" and "tclean"), and just use different
		 * handler routines for distinct command-setup.  The handler
		 * routine might also be set on a generic routine for
		 * initial parameter processing.
		 */
		if (c->c_generic != NULL)
			generic(c->c_generic, c->c_opts, c->c_handler,
			    margc, margv);
		else
			(*c->c_handler)(margc, margv);
	}
}