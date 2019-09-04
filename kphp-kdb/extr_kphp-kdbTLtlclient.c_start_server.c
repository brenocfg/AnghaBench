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

/* Variables and functions */
 int /*<<< orphan*/  NB_alloc ; 
 int /*<<< orphan*/  NB_max ; 
 int /*<<< orphan*/  NB_used ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  add_history (char*) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  connected ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exec_command (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ expect_input ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ log_file ; 
 int /*<<< orphan*/  maxconn ; 
 int now ; 
 int /*<<< orphan*/  pending_signals ; 
 scalar_t__ quit_steps ; 
 char* readline (char*) ; 
 int /*<<< orphan*/  send_rpc_command (char*) ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int start_time ; 
 int strlen (char*) ; 
 char* username ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

void start_server (void) {
  int i;
  int prev_time;

  init_epoll ();
  init_netbuffers ();

  prev_time = 0;

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  create_all_outbound_connections ();

  signal (SIGINT, sigint_handler);
  signal (SIGTERM, sigterm_handler);

  for (i = 0; !pending_signals; i++) {
    if (!(i & 255)) {
      vkprintf (1, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }

    epoll_work (97);

    if (now != prev_time) {
      prev_time = now;
      cron ();
      if (!connected && now - start_time > 10) {
        kprintf ("Didn't connect to server after 10 seconds.\n");
        exit (1);
      }
    }

    if (expect_input) {
      vkprintf (4, "Before readline call.\n");
      char *input = readline ("TL>");
      if (input[0]) {
        int l;
        if (log_file) {
          fprintf (log_file, "TL>%s\n", input);
        }
        add_history (input);
        for (l = strlen (input) - 1; l > 0 && input[l] == ' '; l--) {
          input[l] = 0;
        }

        if (input[0] == '(') {
          send_rpc_command (input);
        } else {
          exec_command (input);
        }
      }
      if (input != NULL) {
        free (input);
      }
    }
    if (quit_steps && !--quit_steps) break;
  }

  cleanup ();

}