#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ output_stdout; scalar_t__ process_and_exit; scalar_t__ stop_processing; } ;
struct TYPE_5__ {int /*<<< orphan*/  processed; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  allocate_holder () ; 
 int /*<<< orphan*/  block_thread_signals () ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  curses_output () ; 
 int /*<<< orphan*/  end_proc ; 
 int /*<<< orphan*/  end_spinner () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  gdns_init () ; 
 TYPE_1__* glog ; 
 int /*<<< orphan*/  house_keeping () ; 
 int /*<<< orphan*/  init_processing () ; 
 int /*<<< orphan*/  initializer () ; 
 int /*<<< orphan*/  output_logerrors (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_cmd_line (int,char**) ; 
 int /*<<< orphan*/  parse_conf_file (int*,char***) ; 
 int /*<<< orphan*/  parse_initial_sort () ; 
 int parse_log (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_curses (int*) ; 
 int /*<<< orphan*/  set_standard_output () ; 
 int /*<<< orphan*/  setup_signal_handlers () ; 
 int /*<<< orphan*/  standard_output () ; 
 int /*<<< orphan*/  start_proc ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_global_config (int,char**) ; 

int
main (int argc, char **argv)
{
  int quit = 0, ret = 0;

  block_thread_signals ();
  setup_signal_handlers ();

  /* command line/config options */
  verify_global_config (argc, argv);
  parse_conf_file (&argc, &argv);
  parse_cmd_line (argc, argv);

  initializer ();

  /* ignore outputting, process only */
  if (conf.process_and_exit) {
  }
  /* set stdout */
  else if (conf.output_stdout) {
    set_standard_output ();
  }
  /* set curses */
  else {
    set_curses (&quit);
  }

  /* no log/date/time format set */
  if (quit)
    goto clean;

  init_processing ();
  /* main processing event */
  time (&start_proc);
  if ((ret = parse_log (&glog, NULL, 0))) {
    end_spinner ();
    goto clean;
  }
  if (conf.stop_processing)
    goto clean;
  glog->offset = glog->processed;

  /* init reverse lookup thread */
  gdns_init ();
  parse_initial_sort ();
  allocate_holder ();

  end_spinner ();
  time (&end_proc);

  /* ignore outputting, process only */
  if (conf.process_and_exit) {
#ifdef TCB_BTREE
    set_accumulated_time ();
#endif
  }
  /* stdout */
  else if (conf.output_stdout) {
    standard_output ();
  }
  /* curses */
  else {
    curses_output ();
  }

  /* clean */
clean:
  /* done, restore tty modes and reset terminal into
   * non-visual mode */
  if (!conf.output_stdout)
    endwin ();

  /* unable to process valid data */
  if (ret)
    output_logerrors (glog);

  house_keeping ();

  return ret ? EXIT_FAILURE : EXIT_SUCCESS;
}