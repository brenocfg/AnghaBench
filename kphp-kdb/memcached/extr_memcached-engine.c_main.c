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
 int LAST_OPER_BUF_SIZE ; 
 int MAX_CONNECTIONS ; 
 scalar_t__ MAX_ZMALLOC_MEM ; 
 int /*<<< orphan*/  MCL_FUTURE ; 
 int /*<<< orphan*/  adjust_oom_score (void*) ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 void* atoi (void*) ; 
 void* backlog ; 
 int daemonize ; 
 int dynamic_data_buffer_size ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_min_memory () ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_hash_table () ; 
 int /*<<< orphan*/  last_oper_type ; 
 void* logname ; 
 int max_memory ; 
 int maxconn ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlockall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nice (void*) ; 
 void* oom_score_adj ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int port ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int return_false_if_not_found ; 
 int rpc_crc32_mode ; 
 int rpc_disable_crc32_check ; 
 scalar_t__ server_socket (int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 void* udp_port ; 
 void* username ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  int i;
  rpc_disable_crc32_check = 1;

  while ((i = getopt (argc, argv, "b:c:l:p:U:m:n:dfhu:vrkO:C:")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'h':
      help();
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
    case 'm':
      max_memory = atoi (optarg);
      max_memory -= get_min_memory();
      if (max_memory < 1) {
        max_memory = 1;
      }
      max_memory *= 1048576;
      break;
    case 'n':
      errno = 0;
      nice (atoi (optarg));
      if (errno) {
        perror ("nice");
      }
      break;
    case 'p':
      port = atoi (optarg);
      break;
    case 'O':
      oom_score_adj = atoi (optarg);
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
    case 'f':
      return_false_if_not_found = 1;
      break;
    case 'r':
      // nothing to do
      break;
    case 'C':
      rpc_crc32_mode = atoi (optarg);
      rpc_disable_crc32_check = (rpc_crc32_mode & 1);
    case 'k':
      break;
      if (mlockall (/* MCL_CURRENT | */ MCL_FUTURE) != 0) {
        fprintf (stderr, "error: fail to lock paged memory\n");
      }
      break;
    }
  }

  if (argc != optind) {
    help();
    return 2;
  }

  if (!username && maxconn == MAX_CONNECTIONS && geteuid()) {
    maxconn = 1000; //not for root
  }

  if (dynamic_data_buffer_size > max_memory) {
    dynamic_data_buffer_size = max_memory;
  }

  if (MAX_ZMALLOC_MEM > 0) {
    init_dyn_data();
  }

  init_hash_table();
#ifdef HISTORY
  memset (last_oper_type, -1, LAST_OPER_BUF_SIZE * sizeof (char));
#endif

  if (raise_file_rlimit (maxconn + 16) < 0) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  if (oom_score_adj) {
    adjust_oom_score (oom_score_adj);
  }

  aes_load_pwd_file (0);

  sfd = server_socket (port, settings_addr, backlog, 0);
  if (sfd < 0) {
    fprintf (stderr, "cannot open server socket at port %d: %m\n", port);
    exit (1);
  }

  start_time = time (NULL);

  start_server();

  return 0;
}