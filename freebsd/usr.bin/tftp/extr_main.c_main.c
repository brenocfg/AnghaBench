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
typedef  int /*<<< orphan*/  History ;
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int acting_as_client ; 
 int /*<<< orphan*/  command (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int command_prompt ; 
 int /*<<< orphan*/ * el_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * history_init () ; 
 int /*<<< orphan*/  init_options () ; 
 int /*<<< orphan*/  intr ; 
 int isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode ; 
 int peer ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpeer (int,char**) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  toplevel ; 
 int /*<<< orphan*/  txrx_error ; 
 int /*<<< orphan*/  urihandling (char*) ; 

int
main(int argc, char *argv[])
{
	HistEvent he;
	static EditLine *el;
	static History *hist;
	bool interactive;

	acting_as_client = 1;
	peer = -1;
	strcpy(mode, "octet");
	signal(SIGINT, intr);

	interactive = isatty(STDIN_FILENO);
	if (interactive) {
		el = el_init("tftp", stdin, stdout, stderr);
		hist = history_init();
		history(hist, &he, H_SETSIZE, 100);
		el_set(el, EL_HIST, history, hist);
		el_set(el, EL_EDITOR, "emacs");
		el_set(el, EL_PROMPT, command_prompt);
		el_set(el, EL_SIGNAL, 1);
		el_source(el, NULL);
	}

	if (argc > 1) {
		if (setjmp(toplevel) != 0)
			exit(txrx_error);

		if (strncmp(argv[1], "tftp://", 7) == 0) {
			urihandling(argv[1]);
			exit(txrx_error);
		}

		setpeer(argc, argv);
	}

	if (setjmp(toplevel) != 0) {
		if (interactive)
			el_reset(el);
		(void)putchar('\n');
	}

	init_options();
	command(interactive, el, hist, &he);
}