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
struct TYPE_2__ {int port; } ;

/* Variables and functions */
 scalar_t__ CSN ; 
 int MAX_CONNECTIONS ; 
 TYPE_1__ PID ; 
 int PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/ * config_filename ; 
 int /*<<< orphan*/  dl_close_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_open_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_set_debug_handlers () ; 
 int dynamic_data_buffer_size ; 
 int /*<<< orphan*/  enable_is_letter_sigils () ; 
 scalar_t__ engine_n ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_all () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  http_port ; 
 int /*<<< orphan*/  init_all () ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_is_letter () ; 
 int /*<<< orphan*/  interactive ; 
 int /*<<< orphan*/  load_time ; 
 int maxconn ; 
 int /*<<< orphan*/  mytime () ; 
 int /*<<< orphan*/  news_port ; 
 int /*<<< orphan*/  no_argument ; 
 void* now ; 
 int optind ; 
 int /*<<< orphan*/  parse_config () ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char,char*,...) ; 
 int port ; 
 char* progname ; 
 int /*<<< orphan*/  queue_parse_option ; 
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
 int use_rpc ; 
 scalar_t__ use_stemmer ; 
 char* username ; 
 int /*<<< orphan*/  watchcat_port ; 

int main (int argc, char *argv[]) {
  dl_set_debug_handlers();
  progname = argv[0];
  now = time (NULL);

  remove_parse_option ('a');
  remove_parse_option ('B');
  remove_parse_option ('r');
  remove_parse_option (204);
  parse_option ("rpc-config", required_argument, NULL, 'C', "<cluster-description-file> description of queue-engine cluster used by rpc");
  parse_option ("total-engines", required_argument, NULL, 'e', "<total_engines> total number of engines");
  parse_option ("http-port", required_argument, 0, 'H', "<port> http port number (default %d)", http_port);
  parse_option ("memory-limit", required_argument, NULL, 'm', "<memory-limit> sets maximal size of used memory not including zmemory for struct conn_query in mebibytes");
  parse_option ("news-port", required_argument, 0, 'N', "<port> port number for communication with other queue-engines in cluster when not using rpc (default %d)", news_port);
  parse_option ("watchcat-port", required_argument, 0, 'P', "<port> port number for communication with watchcats (default %d)", watchcat_port);
  parse_option ("engine-number", required_argument, NULL, 'q', "<engine_number> number of this engine");
  parse_option ("lock-memory", no_argument, NULL, 'k', "lock paged memory");
  parse_option ("stemmer", no_argument, 0, 'S', "enable stemmer");

  parse_engine_options_long (argc, argv, queue_parse_option);
  if (argc != optind + 1) {
    usage();
    return 2;
  }

  PID.port = port;

  init_is_letter();
  enable_is_letter_sigils();
  if (use_stemmer) {
    stem_init();
  }
/*
  fprintf (stderr, "TESTING\n");
  prepare_watchcat_str ("a b c d", 1);
  prepare_watchcat_str ("a a a a", 1);
  prepare_watchcat_str ("    a   a   a   a   ", 1);
  prepare_watchcat_str ("    aaaa   aaa   aaa   aaaaa   ", 1);
  prepare_watchcat_str ("###abc###", 1);
  prepare_watchcat_str ("#a a #b b ##c#d", 1);
  prepare_watchcat_str ("интересно работает ли русский", 1);
  prepare_watchcat_str ("интересно интересный #интересно", 1);
  prepare_watchcat_str ("#test #Test Test #интересный интересный", 1);
  return 0;
*/

//  fprintf (stderr, "config name = %s\n", config_filename);
  if (config_filename != NULL) {
    use_rpc = 1;
  }

  if (use_rpc) {
    dl_open_file (0, config_filename, 0);
    parse_config();
    dl_close_file (0);
    assert (engine_n == CSN);
  }
//  fprintf (stderr, "config parced\n");

  dynamic_data_buffer_size = (1 << 26);//26 for struct conn_query
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
/*
  if (http_port > 0 && http_port < PRIVILEGED_TCP_PORTS) {
    http_sfd = server_socket (http_port, settings_addr, backlog, 0);
    if (http_sfd < 0) {
      fprintf (stderr, "cannot open http server socket at port %d: %m\n", http_port);
      exit (1);
    }
  }*/

  aes_load_pwd_file (NULL);

  if (change_user (username) < 0 && !interactive) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }


  load_time = -mytime();

  init_all();

  load_time += mytime();

  start_time = time (NULL);

  start_server();

  free_all();
  return 0;
}