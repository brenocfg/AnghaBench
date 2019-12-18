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
struct termios {int c_lflag; } ;
typedef  int /*<<< orphan*/  HistEvent ;

/* Variables and functions */
 int ECHO ; 
 int /*<<< orphan*/  EL_ADDFN ; 
 int /*<<< orphan*/  EL_BIND ; 
 int /*<<< orphan*/  EL_EDITMODE ; 
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_GETCFN ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT_ESC ; 
 int /*<<< orphan*/  EL_RESIZE ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  EL_TERMINAL ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  NO_RESET ; 
 int /*<<< orphan*/  RL_PROMPT_START_IGNORE ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/ * _el_rl_complete ; 
 int /*<<< orphan*/ * _el_rl_tstp ; 
 int /*<<< orphan*/  _get_prompt ; 
 int /*<<< orphan*/  _getc_function ; 
 int /*<<< orphan*/  _resize_fun (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rl_update_pos () ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/  el_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  el_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * el_init_internal (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  history_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * history_init () ; 
 scalar_t__ history_length ; 
 int /*<<< orphan*/  max_input_history ; 
 int /*<<< orphan*/  rl_catch_signals ; 
 scalar_t__ rl_getc_function ; 
 scalar_t__ rl_instream ; 
 int /*<<< orphan*/  rl_line_buffer ; 
 scalar_t__ rl_outstream ; 
 int /*<<< orphan*/  rl_readline_name ; 
 int rl_set_prompt (char*) ; 
 int /*<<< orphan*/ * rl_terminal_name ; 
 scalar_t__ stderr ; 
 scalar_t__ stdin ; 
 scalar_t__ stdout ; 
 int tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tty_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
rl_initialize(void)
{
	HistEvent ev;
	int editmode = 1;
	struct termios t;

	if (e != NULL)
		el_end(e);
	if (h != NULL)
		history_end(h);

	if (!rl_instream)
		rl_instream = stdin;
	if (!rl_outstream)
		rl_outstream = stdout;

	/*
	 * See if we don't really want to run the editor
	 */
	if (tcgetattr(fileno(rl_instream), &t) != -1 && (t.c_lflag & ECHO) == 0)
		editmode = 0;

	e = el_init_internal(rl_readline_name, rl_instream, rl_outstream,
	    stderr, fileno(rl_instream), fileno(rl_outstream), fileno(stderr),
	    NO_RESET);

	if (!editmode)
		el_set(e, EL_EDITMODE, 0);

	h = history_init();
	if (!e || !h)
		return -1;

	history(h, &ev, H_SETSIZE, INT_MAX);	/* unlimited */
	history_length = 0;
	max_input_history = INT_MAX;
	el_set(e, EL_HIST, history, h);

	/* Setup resize function */
	el_set(e, EL_RESIZE, _resize_fun, &rl_line_buffer);

	/* setup getc function if valid */
	if (rl_getc_function)
		el_set(e, EL_GETCFN, _getc_function);

	/* for proper prompt printing in readline() */
	if (rl_set_prompt("") == -1) {
		history_end(h);
		el_end(e);
		return -1;
	}
	el_set(e, EL_PROMPT_ESC, _get_prompt, RL_PROMPT_START_IGNORE);
	el_set(e, EL_SIGNAL, rl_catch_signals);

	/* set default mode to "emacs"-style and read setting afterwards */
	/* so this can be overridden */
	el_set(e, EL_EDITOR, "emacs");
	if (rl_terminal_name != NULL)
		el_set(e, EL_TERMINAL, rl_terminal_name);
	else
		el_get(e, EL_TERMINAL, &rl_terminal_name);

	/*
	 * Word completion - this has to go AFTER rebinding keys
	 * to emacs-style.
	 */
	el_set(e, EL_ADDFN, "rl_complete",
	    "ReadLine compatible completion function",
	    _el_rl_complete);
	el_set(e, EL_BIND, "^I", "rl_complete", NULL);

	/*
	 * Send TSTP when ^Z is pressed.
	 */
	el_set(e, EL_ADDFN, "rl_tstp",
	    "ReadLine compatible suspend function",
	    _el_rl_tstp);
	el_set(e, EL_BIND, "^Z", "rl_tstp", NULL);

	/*
	 * Set some readline compatible key-bindings.
	 */
	el_set(e, EL_BIND, "^R", "em-inc-search-prev", NULL);

	/*
	 * Allow the use of Home/End keys.
	 */
	el_set(e, EL_BIND, "\\e[1~", "ed-move-to-beg", NULL);
	el_set(e, EL_BIND, "\\e[4~", "ed-move-to-end", NULL);
	el_set(e, EL_BIND, "\\e[7~", "ed-move-to-beg", NULL);
	el_set(e, EL_BIND, "\\e[8~", "ed-move-to-end", NULL);
	el_set(e, EL_BIND, "\\e[H", "ed-move-to-beg", NULL);
	el_set(e, EL_BIND, "\\e[F", "ed-move-to-end", NULL);

	/*
	 * Allow the use of the Delete/Insert keys.
	 */
	el_set(e, EL_BIND, "\\e[3~", "ed-delete-next-char", NULL);
	el_set(e, EL_BIND, "\\e[2~", "ed-quoted-insert", NULL);

	/*
	 * Ctrl-left-arrow and Ctrl-right-arrow for word moving.
	 */
	el_set(e, EL_BIND, "\\e[1;5C", "em-next-word", NULL);
	el_set(e, EL_BIND, "\\e[1;5D", "ed-prev-word", NULL);
	el_set(e, EL_BIND, "\\e[5C", "em-next-word", NULL);
	el_set(e, EL_BIND, "\\e[5D", "ed-prev-word", NULL);
	el_set(e, EL_BIND, "\\e\\e[C", "em-next-word", NULL);
	el_set(e, EL_BIND, "\\e\\e[D", "ed-prev-word", NULL);

	/* read settings from configuration file */
	el_source(e, NULL);

	/*
	 * Unfortunately, some applications really do use rl_point
	 * and rl_line_buffer directly.
	 */
	_resize_fun(e, &rl_line_buffer);
	_rl_update_pos();

	tty_end(e, TCSADRAIN);

	return 0;
}