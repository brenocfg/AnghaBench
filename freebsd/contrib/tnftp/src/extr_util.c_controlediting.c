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
typedef  int /*<<< orphan*/  HistEvent ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ADDFN ; 
 int /*<<< orphan*/  EL_BIND ; 
 int /*<<< orphan*/  EL_EDITMODE ; 
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 int /*<<< orphan*/  EL_RPROMPT ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 int /*<<< orphan*/  complete ; 
 scalar_t__ editing ; 
 int /*<<< orphan*/ * el ; 
 int /*<<< orphan*/  el_end (int /*<<< orphan*/ *) ; 
 int el_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * el_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getprogname () ; 
 int /*<<< orphan*/ * hist ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  history_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * history_init () ; 
 int prompt ; 
 int rprompt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ttyout ; 

void
controlediting(void)
{
	if (editing && el == NULL && hist == NULL) {
		HistEvent ev;
		int editmode;

		el = el_init(getprogname(), stdin, ttyout, stderr);
		/* init editline */
		hist = history_init();		/* init the builtin history */
		history(hist, &ev, H_SETSIZE, 100);/* remember 100 events */
		el_set(el, EL_HIST, history, hist);	/* use history */

		el_set(el, EL_EDITOR, "emacs");	/* default editor is emacs */
		el_set(el, EL_PROMPT, prompt);	/* set the prompt functions */
		el_set(el, EL_RPROMPT, rprompt);

		/* add local file completion, bind to TAB */
		el_set(el, EL_ADDFN, "ftp-complete",
		    "Context sensitive argument completion",
		    complete);
		el_set(el, EL_BIND, "^I", "ftp-complete", NULL);
		el_source(el, NULL);	/* read ~/.editrc */
		if ((el_get(el, EL_EDITMODE, &editmode) != -1) && editmode == 0)
			editing = 0;	/* the user doesn't want editing,
					 * so disable, and let statement
					 * below cleanup */
		else
			el_set(el, EL_SIGNAL, 1);
	}
	if (!editing) {
		if (hist) {
			history_end(hist);
			hist = NULL;
		}
		if (el) {
			el_end(el);
			el = NULL;
		}
	}
}