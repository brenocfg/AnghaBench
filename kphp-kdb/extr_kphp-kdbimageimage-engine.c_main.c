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
 int MAX_CHILD_PROCESS ; 
 int MAX_CONNECTIONS ; 
 int MAX_THREADS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atoi (void*) ; 
 void* backlog ; 
 scalar_t__ change_user_group (char*,char*) ; 
 int daemonize ; 
 int dynamic_data_buffer_size ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 char* groupname ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int job_nice ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kprintf_multiprocessing_mode_enable () ; 
 void* logname ; 
 int main_nice ; 
 long long max_all_results ; 
 long long max_load_image_area ; 
 int max_process_number ; 
 long long max_virtual_memory ; 
 int maxconn ; 
 long long memory_limit ; 
 scalar_t__ nice (int) ; 
 void* optarg ; 
 int port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int /*<<< orphan*/  req_structures_init () ; 
 long long rss_memory_limit ; 
 scalar_t__ server_socket (int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int sscanf (void*,char*,long long*,char*) ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int threads_limit ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int main (int argc, char *argv[]) {
  int i, k;
  long long x;
  char c;

  set_debug_handlers ();
  progname = argv[0];
  while ((i = getopt (argc, argv, "A:H:M:N:P:R:T:b:c:g:l:n:p:dhu:v")) != -1) {
    switch (i) {
     case 'A':
     case 'H':
     case 'M':
     case 'R':
       c = 0;
       assert (sscanf (optarg, "%lld%c", &x, &c) >= 1);
       switch (c | 0x20) {
         case 'k':  x <<= 10; break;
         case 'm':  x <<= 20; break;
         case 'g':  x <<= 30; break;
         case 't':  x <<= 40; break;
         default: assert (c == 0x20);
       }
       if (i == 'A' && x >= (1 << 20) && x <= (1 << 30)) {
         max_load_image_area = x;
       }
       if (i == 'H' && x >= (1LL << 20) && x <= max_virtual_memory) {
         max_all_results = x;
       }
       if (i == 'M' && x >= (128LL << 20) && x <= max_virtual_memory) {
         memory_limit = x;
       }
       if (i == 'R' && x >= (64LL << 20) && x <= rss_memory_limit) {
         rss_memory_limit = x;
       }
       break;
    case 'N':
      job_nice = atoi (optarg);
      break;
    case 'P':
      k = atoi (optarg);
      if (k >= 1 && k <= MAX_CHILD_PROCESS) {
        max_process_number = k;
      }
      break;
    case 'T':
      k = atoi (optarg);
      if (k >= 1 && k <= MAX_THREADS) {
        threads_limit = k;
      }
      break;
    case 'v':
      verbosity++;
      break;
    case 'g':
      groupname = optarg;
      break;
    case 'h':
      usage ();
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
    case 'n':
      main_nice = atoi (optarg);
      break;
    case 'p':
      port = atoi (optarg);
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

  if (max_process_number) {
    kprintf_multiprocessing_mode_enable ();
  } else {
    kprintf ("max-child-process-number isn't stricly positive\n");
    usage ();
  }

  if (job_nice < main_nice) {
    kprintf ("Job process nice is smaller than main process nice.\nSee man 2 nice: Only the super user may specify a negative increment, or priority increase.\n");
    usage ();
  }

  if (main_nice < -20 || main_nice > 19) {
    kprintf ("Main process nice should be in the range -20 to 19.\n");
    exit (1);
  }

  if (job_nice < -20 || job_nice > 19) {
    kprintf ("Job process nice should be in the range -20 to 19.\n");
    exit (1);
  }

  if (nice (main_nice) < 0) {
    kprintf ("nice (%d) fail. %m\n", main_nice);
    exit (1);
  }

  vkprintf (3, "Command line parsed\n");

  if (!username && maxconn == MAX_CONNECTIONS && geteuid ()) {
    maxconn = 1000; //not for root
  }

  dynamic_data_buffer_size = 1 << 22;

  if (raise_file_rlimit (maxconn + 16) < 0) {
    kprintf ("fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  aes_load_pwd_file (0);

  if (change_user_group (username, groupname) < 0) {
    kprintf ("fatal: cannot change user to %s, group to %s\n", username ? username : "(none)", groupname ? groupname : "(none)");
    exit (1);
  }

  init_dyn_data();

  sfd = server_socket (port, settings_addr, backlog, 0);
  if (sfd < 0) {
    kprintf ("cannot open server socket at port %d: %m\n", port);
    exit (1);
  }

  req_structures_init ();
  start_time = time(0);

  start_server ();
  return 0;
}