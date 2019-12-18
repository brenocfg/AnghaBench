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
struct TYPE_6__ {scalar_t__ output_format_idx; scalar_t__ daemonize; scalar_t__ real_time_html; } ;
struct TYPE_5__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*) ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  daemonize () ; 
 scalar_t__ find_output_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gwsreader ; 
 int /*<<< orphan*/  gwswriter ; 
 TYPE_1__* new_gwsreader () ; 
 int /*<<< orphan*/  new_gwswriter () ; 
 int open_fifoout () ; 
 int /*<<< orphan*/  parsing_spinner ; 
 int /*<<< orphan*/  setup_thread_signals () ; 
 int /*<<< orphan*/  setup_ws_server (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ui_spinner_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_standard_output (void)
{
  int html = 0;
  gwswriter = new_gwswriter ();
  gwsreader = new_gwsreader ();

  /* HTML */
  if (find_output_type (NULL, "html", 0) == 0 || conf.output_format_idx == 0)
    html = 1;

  /* Spawn WebSocket server threads */
  if (html && conf.real_time_html) {
    /* open fifo for read */
    if ((gwsreader->fd = open_fifoout ()) == -1) {
      LOG (("Unable to open FIFO for read.\n"));
      return;
    }

    if (conf.daemonize)
      daemonize ();
    setup_ws_server (gwswriter, gwsreader);
  }
  setup_thread_signals ();

  /* Spawn progress spinner thread */
  ui_spinner_create (parsing_spinner);
}