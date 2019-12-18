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
struct TYPE_2__ {int stop_processing; int /*<<< orphan*/  output_stdout; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
#define  SIGINT 130 
#define  SIGPIPE 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gwsreader ; 
 int /*<<< orphan*/  gwswriter ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_ws_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_signal_action (int sig_number)
{
  switch (sig_number) {
  case SIGTERM:
  case SIGINT:
    fprintf (stderr, "\nSIGINT caught!\n");
    fprintf (stderr, "Closing GoAccess...\n");

    stop_ws_server (gwswriter, gwsreader);
    conf.stop_processing = 1;

    if (!conf.output_stdout) {
      cleanup(EXIT_SUCCESS);
      exit(EXIT_SUCCESS);
    }

    break;
  case SIGPIPE:
    fprintf (stderr, "SIGPIPE caught!\n");
    /* ignore it */
    break;
  }
}