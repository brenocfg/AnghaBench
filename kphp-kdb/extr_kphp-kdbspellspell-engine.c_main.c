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
 void* BACKLOG ; 
 scalar_t__ MAX_CONNECTIONS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 void* atoi (void*) ; 
 void* backlog ; 
 scalar_t__ change_user (char*) ; 
 int daemonize ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 void* logname ; 
 scalar_t__ maxconn ; 
 void* optarg ; 
 char* port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 scalar_t__ server_socket (char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  spell_done ; 
 int /*<<< orphan*/  spell_init () ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int test_mode ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 void* udp_port ; 
 int use_aspell_suggestion ; 
 char* username ; 
 int /*<<< orphan*/  verbosity ; 
 int yo_hack ; 

int main (int argc, char *argv[]) {
  int i;
  //int k;
  //long long x;
  //char c;

  set_debug_handlers ();

  progname = argv[0];
  while ((i = getopt (argc, argv, "b:c:l:p:U:dhu:vSty")) != -1) {
    switch (i) {
    case 'y':
      yo_hack = 1;
    break;
    case 't':
      test_mode = 1;
    break;
    case 'S':
      use_aspell_suggestion = 1;
    break;
    case 'v':
      verbosity++;
      break;
    case 'h':
      help ();
      return 2;
    case 'b':
      backlog = atoi (optarg);
      if (backlog <= 0) {
        backlog = BACKLOG;
      }
      break;
    case 'c':
      maxconn = atoi (optarg);
      if (maxconn <= 0 || maxconn > MAX_CONNECTIONS) {
        maxconn = MAX_CONNECTIONS;
      }
      break;
    case 'p':
      port = atoi (optarg);
      break;
    case 'U':
      udp_port = atoi (optarg);
      break;
    case 'u':
      username = optarg;
      break;
    case 'l':
      logname = optarg;
      break;
    case 'd':
      daemonize ^= 1;
      break;
    }
  }

  //dynamic_data_buffer_size = 1 << 22;

  if (raise_file_rlimit (maxconn + 16) < 0) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }
  
  sfd = server_socket (port, settings_addr, backlog, 0);
  if (sfd < 0) {
    kprintf ("cannot open server socket at port %d: %m\n", port);
    exit (1);
  }

  aes_load_pwd_file (0);

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_dyn_data ();

  start_time = time (0);
  spell_init ();
  atexit (spell_done);

  start_server ();
  return 0;
}