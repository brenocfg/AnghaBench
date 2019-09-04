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
 scalar_t__ CLIENT ; 
 scalar_t__ SERVER ; 
 char* TFTP_PORT ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 scalar_t__ change_user (char*) ; 
 scalar_t__ check_source_dirname () ; 
 int /*<<< orphan*/  compute_tmp_filename () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_msg_buffers (int /*<<< orphan*/ ) ; 
 char* input_filename ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int /*<<< orphan*/  max_port ; 
 char* maxconn ; 
 int /*<<< orphan*/  min_port ; 
 scalar_t__ open_udp_server_socket (char*) ; 
 int optind ; 
 char* output_filename ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char*,...) ; 
 char* port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (char*) ; 
 int /*<<< orphan*/  remove_parse_option (char) ; 
 int /*<<< orphan*/  required_argument ; 
 scalar_t__ server_sfd ; 
 int /*<<< orphan*/  signals_init () ; 
 char* source_dirname ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 scalar_t__ working_mode ; 

int main (int argc, char *argv[]) {
  signals_init ();
  progname = argv[0];

  remove_parse_option ('r'); //disable replica (no binlogs)
  remove_parse_option ('a');
  remove_parse_option ('B');

  parse_option ("server-port-range", required_argument, 0, 'R', "sets server port's range. Default range is '%d-%d'. Every UDP connection use one port.", min_port, max_port);
  parse_option ("client-blksize", required_argument, 0, 'B', "sets packet block size");
  parse_option ("client-timeout", required_argument, 0, 'T', "sets timeout in seconds");
  parse_option ("stats-port", required_argument, 0, 'P', "sets port for getting stats using memcache queries");
  parse_engine_options_long (argc, argv, f_parse_option);

  if (argc == optind + 1) {
    working_mode = SERVER;
    source_dirname = argv[optind];
  } else if (argc == optind + 2) {
    input_filename = argv[optind];
    output_filename = argv[optind+1];
    compute_tmp_filename ();
    working_mode = CLIENT;
  } else {
    usage ();
  }

  init_epoll ();

  if (!port) {
    port = TFTP_PORT;
  }

  if (working_mode == SERVER) {
    server_sfd = open_udp_server_socket (port);
    if (server_sfd < 0) {
      kprintf ("Fail to open UDP server socket on the port %d.\n", port);
      exit (1);
    }
  }

  if (raise_file_rlimit (maxconn + 16) < 0) {
    kprintf ("fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  aes_load_pwd_file (0); //srand48

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_dyn_data ();
  if (working_mode == SERVER) {
    if (check_source_dirname () < 0) {
      exit (1);
    }
  }
  init_msg_buffers (0);
  start_time = time (NULL);
  start_server ();
  return 0;
}