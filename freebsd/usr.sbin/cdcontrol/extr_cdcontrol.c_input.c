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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  History ;
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int CMD_QUIT ; 
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 int MAXLINE ; 
 int cdcontrol_prompt ; 
 char* el_gets (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * el_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * history_init () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* parse (char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 

__attribute__((used)) static char *
input(int *cmd)
{
#define MAXLINE 80
	static EditLine *el = NULL;
	static History *hist = NULL;
	HistEvent he;
	static char buf[MAXLINE];
	int num = 0;
	int len;
	const char *bp = NULL;
	char *p;

	do {
		if (verbose) {
			if (!el) {
				el = el_init("cdcontrol", stdin, stdout,
				    stderr);
				hist = history_init();
				history(hist, &he, H_SETSIZE, 100);
				el_set(el, EL_HIST, history, hist);
				el_set(el, EL_EDITOR, "emacs");
				el_set(el, EL_PROMPT, cdcontrol_prompt);
				el_set(el, EL_SIGNAL, 1);
				el_source(el, NULL);
			}
			if ((bp = el_gets(el, &num)) == NULL || num == 0) {
				*cmd = CMD_QUIT;
				fprintf (stderr, "\r\n");
				return (0);
			}

			len = (num > MAXLINE) ? MAXLINE : num;
			memcpy(buf, bp, len);
			buf[len] = 0;
			history(hist, &he, H_ENTER, bp);
#undef MAXLINE

		} else {
			if (! fgets (buf, sizeof (buf), stdin)) {
				*cmd = CMD_QUIT;
				fprintf (stderr, "\r\n");
				return (0);
			}
		}
		p = parse (buf, cmd);
	} while (! p);
	return (p);
}