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
struct TYPE_2__ {scalar_t__ port; } ;

/* Variables and functions */
 TYPE_1__ PID ; 
 int /*<<< orphan*/  PING_INTERVAL ; 
 scalar_t__ PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_pwd_file ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ bname ; 
 char* config_filename ; 
 int do_reload_config (int /*<<< orphan*/ ) ; 
 scalar_t__ enable_ipv6 ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_my_ipv4 () ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_server_PID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__) ; 
 int maxconn ; 
 int /*<<< orphan*/  no_argument ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char*,...) ; 
 scalar_t__ port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int /*<<< orphan*/  read_binlog (scalar_t__) ; 
 int /*<<< orphan*/  remove_parse_option (char) ; 
 int /*<<< orphan*/  required_argument ; 
 int rpc_disable_crc32_check ; 
 scalar_t__ server_socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_mode ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ usfd ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int main (int argc, char *argv[]) {
  rpc_disable_crc32_check = 1;
  int i;

  set_debug_handlers ();

  progname = argv[0];

  remove_parse_option ('B');
  parse_option ("first-cluster-only", required_argument, 0, 'f', "only first cluster");
  parse_option ("test-mode", no_argument, 0, 'T', 0);
  parse_option ("tcp-buffers", no_argument, 0, 'N', "new tcp buffers");
  parse_option ("crc32-mode", required_argument, 0, 'C', "crc32 mode: bit 0 disables crc32 check, bit 1 disables crc32 send (sends 0)");
  parse_option ("heap-size", required_argument, 0, 'H', "sets heap size. Supports K/M/G/T modifiers");
  parse_option ("max-binlog-size", required_argument, 0, 'S', "sets maximal binlog slice size. Supports K/M/G/T modifiers");
  parse_option ("ping-interval", required_argument, 0, 'y', "sets ping interval (only in tcp connections) (default %lf)", PING_INTERVAL);
  parse_option ("binlog-enable", required_argument, 0, 'B', "enables binlog mode. argument is binlog name");
  parse_option ("drop-probability", required_argument, 0, 'Q', "sets probability of dropping transmitted packet");
  parse_option (0, required_argument, 0, 'n', "sets niceness");

  parse_engine_options_long (argc, argv, f_parse_option);
  if (argc != optind + 1) {
    usage();
    return 2;
  }

  PID.port = port;
  init_dyn_data ();
  init_server_PID (get_my_ipv4 (), port);

  if (raise_file_rlimit (maxconn + 16) < 0 && !test_mode) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit (1);
  }

  config_filename = argv[optind];

  i = do_reload_config (0);

  if (i < 0) {
    fprintf (stderr, "config check failed!\n");
    return -i;
  }

  vkprintf (1, "config loaded!\n");

  aes_load_pwd_file (aes_pwd_file);

  if (port < PRIVILEGED_TCP_PORTS) {
    sfd = server_socket (port, settings_addr, backlog, enable_ipv6);
    if (sfd < 0) {
      kprintf ("cannot open server socket at port %d: %m\n", port);
      exit (1);
    }
    usfd = server_socket (port, settings_addr, backlog, enable_ipv6 + 1);
    if (usfd < 0) {
      kprintf ("cannot open udp server socket at port %d: %m\n", port);
      exit (1);
    }
  }

  if (bname) {
    read_binlog (bname);
  }
  start_time = time (0);

  start_server ();

  return 0;
}