#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int no_color; scalar_t__ read_stdin; scalar_t__ load_conf_dlg; int /*<<< orphan*/  color_scheme; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FATAL (char*,char const*) ; 
 int /*<<< orphan*/  NO_COLOR ; 
 int /*<<< orphan*/  clear () ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  glog ; 
 scalar_t__ has_colors () ; 
 int /*<<< orphan*/  header_win ; 
 int /*<<< orphan*/  init_colors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_windows (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_win ; 
 int /*<<< orphan*/  parsing_spinner ; 
 int /*<<< orphan*/  refresh () ; 
 int render_confdlg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_curses_spinner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input_opts () ; 
 int /*<<< orphan*/  setup_thread_signals () ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  ui_spinner_create (int /*<<< orphan*/ ) ; 
 char* verify_formats () ; 

__attribute__((used)) static void
set_curses (int *quit)
{
  const char *err_log = NULL;

  setup_thread_signals ();
  set_input_opts ();
  if (conf.no_color || has_colors () == FALSE) {
    conf.color_scheme = NO_COLOR;
    conf.no_color = 1;
  } else {
    start_color ();
  }
  init_colors (0);
  init_windows (&header_win, &main_win);
  set_curses_spinner (parsing_spinner);

  /* Display configuration dialog if missing formats and not piping data in */
  if (!conf.read_stdin && (verify_formats () || conf.load_conf_dlg)) {
    refresh ();
    *quit = render_confdlg (glog, parsing_spinner);
    clear ();
  }
  /* Piping data in without log/date/time format */
  else if (conf.read_stdin && (err_log = verify_formats ())) {
    FATAL ("%s", err_log);
  }
  /* straight parsing */
  else {
    ui_spinner_create (parsing_spinner);
  }
}