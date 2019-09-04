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
 int MAX_CONNECTIONS ; 
 int PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  dl_set_debug_handlers () ; 
 int dynamic_data_buffer_size ; 
 int /*<<< orphan*/  enable_is_letter_sigils () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_all () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  init_all () ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_is_letter () ; 
 int /*<<< orphan*/  interactive ; 
 int maxconn ; 
 int /*<<< orphan*/  no_argument ; 
 void* now ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char,char*,...) ; 
 int port ; 
 char* progname ; 
 int /*<<< orphan*/  queue_port ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int /*<<< orphan*/  remove_parse_option (int) ; 
 int /*<<< orphan*/  required_argument ; 
 scalar_t__ server_socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  start_server () ; 
 void* start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stem_init () ; 
 void* time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ use_stemmer ; 
 char* username ; 
 int /*<<< orphan*/  watchcat_parse_option ; 

int main (int argc, char *argv[]) {
  dl_set_debug_handlers ();
  progname = argv[0];
  now = time (NULL);

  remove_parse_option ('a');
  remove_parse_option ('B');
  remove_parse_option ('r');
  remove_parse_option (204);
  parse_option ("memory-limit", required_argument, NULL, 'm', "<memory-limit> sets maximal size of used memory not including zmemory in mebibytes");
  parse_option ("queue-port", required_argument, 0, 'P', "<port> port number for communication with queue (default %d)", queue_port);
  parse_option ("lock-memory", no_argument, NULL, 'k', "lock paged memory");
  parse_option ("stemmer", no_argument, 0, 'S', "enable stemmer");

  parse_engine_options_long (argc, argv, watchcat_parse_option);
  if (argc != optind) {
    usage();
    return 2;
  }

  init_is_letter();
  enable_is_letter_sigils();
  if (use_stemmer) {
    stem_init();
  }

  dynamic_data_buffer_size = (1 << 20);
  init_dyn_data();

  if (!username && maxconn == MAX_CONNECTIONS && geteuid()) {
    maxconn = 1000; //not for root
  }

  if (raise_file_rlimit (maxconn + 16) < 0) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  if (port < PRIVILEGED_TCP_PORTS) {
    sfd = server_socket (port, settings_addr, backlog, 0);
    if (sfd < 0) {
      fprintf (stderr, "cannot open server socket at port %d: %m\n", port);
      exit (1);
    }
  }

  aes_load_pwd_file (NULL);

  if (change_user (username) < 0 && !interactive) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_all();
  start_time = time (NULL);

  start_server();

  free_all();
  return 0;
}