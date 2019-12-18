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
 scalar_t__ DEBUG_FILEDUMP ; 
 scalar_t__ DEBUG_UDPDUMP ; 
 scalar_t__ DHCP_PORT ; 
 scalar_t__ PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 scalar_t__ change_user (char*) ; 
 scalar_t__ debug_mode ; 
 scalar_t__ dhcp_config_load (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 scalar_t__ file_dump (char*) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_msg_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 char* maxconn ; 
 int /*<<< orphan*/  no_argument ; 
 int /*<<< orphan*/  open_server_sockets () ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,char*) ; 
 scalar_t__ port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (char*) ; 
 int /*<<< orphan*/  signals_init () ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 

int main (int argc, char *argv[]) {
  signals_init ();
  progname = argv[0];

  parse_option ("debug-udpdump", no_argument, 0, 'U', "listen 67/68 ports and dump received packets to the log");
  parse_option ("debug-filedump", no_argument, 0, 'F', "parse packet from file (filename is given in <config> parameter) and exit");

  parse_engine_options_long (argc, argv, f_parse_option);

  if (argc != optind + 1) {
    usage ();
  }

  if (debug_mode == DEBUG_FILEDUMP) {
    exit ((file_dump (argv[optind]) < 0) ? 1 : 0);
  }

  if (!port || debug_mode == DEBUG_UDPDUMP) {
    port = DHCP_PORT;
  }

  if (port < PRIVILEGED_TCP_PORTS) {
    open_server_sockets ();
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
  init_msg_buffers (0);

  if (dhcp_config_load (argv[optind]) < 0) {
    kprintf ("fatal: fail to load config file '%s'.\n", argv[optind]);
    exit (1);
  }

  start_time = time (NULL);
  start_server ();
  return 0;
}