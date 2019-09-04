#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct worker_stats {int dummy; } ;
struct related_binlog_status {int dummy; } ;
struct related_binlog {int dummy; } ;
struct TYPE_10__ {scalar_t__ port; } ;
struct TYPE_9__ {scalar_t__ port; } ;
struct TYPE_8__ {int status; TYPE_1__* binlog; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int BACKLOG ; 
 TYPE_2__* LR ; 
 int MAP_ANONYMOUS ; 
 int MAP_SHARED ; 
 scalar_t__ MAX_CONNECTIONS ; 
 TYPE_5__ PID ; 
 int /*<<< orphan*/  PING_INTERVAL ; 
 scalar_t__ PRIVILEGED_TCP_PORTS ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int RBStats ; 
 int /*<<< orphan*/  SM_IPV6 ; 
 int WStats ; 
 int /*<<< orphan*/  aes_load_pwd_file (void*) ; 
 void* aes_pwd_file ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atof (void*) ; 
 int atoi (void*) ; 
 int backlog ; 
 int /*<<< orphan*/  binlog_disabled ; 
 scalar_t__ change_user (char*) ; 
 int check_all_locations ; 
 scalar_t__ check_binlog_files () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 char* config_filename ; 
 int daemonize ; 
 TYPE_4__ default_ct ; 
 scalar_t__ default_target_port ; 
 int /*<<< orphan*/  detect_hostname () ; 
 int double_send_recv ; 
 long long dynamic_data_buffer_size ; 
 int /*<<< orphan*/  enable_ipv6 ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fd ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int getppid () ; 
 char* hostname ; 
 int /*<<< orphan*/  hostname_len ; 
 int /*<<< orphan*/  init_common_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_monitor (int) ; 
 int /*<<< orphan*/  kdb_hosts_loaded ; 
 int /*<<< orphan*/  kdb_load_hosts () ; 
 int /*<<< orphan*/  kprintf_multiprocessing_mode_enable () ; 
 void* last_handshake_id ; 
 void* last_session_id ; 
 int local_rbs ; 
 void* logname ; 
 void* lrand48 () ; 
 scalar_t__ maxconn ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int mmap (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int monitor_priority ; 
 int /*<<< orphan*/  open_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* optarg ; 
 int optind ; 
 int orig_local_rbs ; 
 int parent_pid ; 
 int parse_config (int /*<<< orphan*/ ) ; 
 int* pids ; 
 int /*<<< orphan*/  ping_interval ; 
 scalar_t__ port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  rescan_pid_table () ; 
 scalar_t__ server_socket (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int slave_mode ; 
 int /*<<< orphan*/  srand48 (int /*<<< orphan*/ ) ; 
 int sscanf (void*,char*,long long*,char*) ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*,int) ; 
 int worker_id ; 
 int workers ; 

int main (int argc, char *argv[]) {
  int i, syntax_check = 0;
  long long x;
  char c;

  set_debug_handlers ();
  srand48 (rdtsc());

  progname = argv[0];
  while ((i = getopt (argc, argv, "6CDH:LM:P:T:Z:b:c:dhl:p:q:ru:v")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'h':
      usage();
      return 2;
    case 'C':
      syntax_check = 1;
      break;
    case 'D':
      double_send_recv = 1;
      break;
    case 'L':
      check_all_locations = 1;
      break;
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
      port = atoi(optarg);
      break;
    case 'u':
      username = optarg;
      break;
    case 'l':
      logname = optarg;
      break;
    case 'r':
      binlog_disabled++;
      break;
    case 'd':
      daemonize ^= 1;
      break;
    case 'P':
      aes_pwd_file = optarg;
      break;
    case 'H':
      hostname = optarg;
      break;
    case 'M':
      workers = atoi (optarg);
      assert (workers >= 0);
      break;
    case 'Z':
      c = 0;
      assert (sscanf (optarg, "%lld%c", &x, &c) >= 1);
      switch (c | 0x20) {
      case 'k':  x <<= 10; break;
      case 'm':  x <<= 20; break;
      case 'g':  x <<= 30; break;
      case 't':  x <<= 40; break;
      default: assert (c == 0x20);
      }
      if (x >= (1LL << 20) && x <= (sizeof(long) == 4 ? (3LL << 30) : (100LL << 30))) {
        dynamic_data_buffer_size = x;
      }
      break;
    case '6':
      enable_ipv6 = SM_IPV6;
      break;
    case 'q':
      monitor_priority = atoi (optarg) & 3;
      break;
    case 'T':
      ping_interval = atof (optarg);
      if (ping_interval <= 0) {
        ping_interval = PING_INTERVAL;
      }
      break;
    default:
      assert (0);
    }
  }
  if (argc != optind + 1) {
    usage();
    return 2;
  }

  PID.port = port;
  default_ct.port = port;
  default_target_port = port;

  detect_hostname ();
  hostname_len = strlen (hostname);

  if (raise_file_rlimit (maxconn + 16) < 0) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit (1);
  }

  if (port < PRIVILEGED_TCP_PORTS) {
    sfd = server_socket (port, settings_addr, backlog, enable_ipv6);
    if (sfd < 0) {
      fprintf (stderr, "cannot open server socket at port %d: %m\n", port);
      exit (1);
    }
  }

  init_dyn_data();

  config_filename = argv[optind];

  open_file (0, config_filename, 0);
  i = parse_config (0);

  close (fd[0]);

  if (i < 0) {
    fprintf (stderr, "config check failed!\n");
    return -i;
  }

  if (verbosity > 0) {
    fprintf (stderr, "config loaded!\n");
  }

  if (workers > local_rbs) {
    workers = local_rbs;
  }

  if (syntax_check) {
    return 0;
  }

  if (!local_rbs) {
    fprintf (stderr, "nothing to do: no related binlogs found in %s for hostname %s, exiting\n", config_filename, hostname);
    exit (0);
  }

  if (daemonize && !workers) {
    setsid();
  }

  orig_local_rbs = local_rbs;

  RBStats = mmap (0, 2 * local_rbs * sizeof (struct related_binlog_status), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  assert (RBStats);

  for (i = 0; i < local_rbs; i++) {
    LR[i].status = RBStats + 2 * i;
  }

  if (workers) {
    if (!kdb_hosts_loaded) {
      kdb_load_hosts ();
    }
    for (i = 0; i < local_rbs; i++) {
      assert (!(LR[i].binlog->flags & 4));
    }
    WStats = mmap (0, 2 * workers * sizeof (struct worker_stats), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert (WStats);
    kprintf_multiprocessing_mode_enable ();
    vkprintf (0, "creating %d workers\n", workers);
    for (i = 0; i < workers; i++) {
      int pid = fork ();
      assert (pid >= 0);
      if (!pid) {
        int j = i, k = 0;
        while (j < local_rbs) {
          memcpy (LR + k, LR + j, sizeof (struct related_binlog));
          j += workers;
          k++;
        }
        worker_id = i;
        local_rbs = k;
        workers = 0;
        slave_mode = 1;
        parent_pid = getppid ();
        assert (parent_pid > 1);
        break;
      } else {
        pids[i] = pid;
      }
    }
  }

  aes_load_pwd_file (aes_pwd_file);

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  if (check_binlog_files () <= 0 && !workers) {
    fprintf (stderr, "fatal: do not have needed binlog files\n");
    exit (3);
  }

  if (workers) {
    local_rbs = 0;
  }

  init_common_data (0, 0);

  start_time = time(0);

  if (!slave_mode) {
    init_monitor (monitor_priority);
  }
  rescan_pid_table ();

  last_handshake_id = lrand48 ();
  last_session_id = lrand48 ();

  start_server();

  return 0;
}