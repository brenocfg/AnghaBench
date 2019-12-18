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
 int CLUSTER_MODE_ANTISPAM ; 
 int CLUSTER_MODE_BAYES ; 
 int CLUSTER_MODE_DOT ; 
 int CLUSTER_MODE_FRIENDS ; 
 int CLUSTER_MODE_HINTS ; 
 int CLUSTER_MODE_HINTS_MERGE ; 
 int CLUSTER_MODE_LISTS ; 
 int CLUSTER_MODE_LOGS ; 
 int CLUSTER_MODE_MAGUS ; 
 int CLUSTER_MODE_MERGE ; 
 int CLUSTER_MODE_NEWS ; 
 int CLUSTER_MODE_NEWSR ; 
 int CLUSTER_MODE_NEWS_COMM ; 
 int CLUSTER_MODE_NEWS_G ; 
 int CLUSTER_MODE_NEWS_UG ; 
 int CLUSTER_MODE_PHOTO ; 
 int CLUSTER_MODE_RANDOM_MERGE ; 
 int CLUSTER_MODE_ROUNDROBIN ; 
 int CLUSTER_MODE_SEARCH ; 
 int CLUSTER_MODE_SEARCHX ; 
 int CLUSTER_MODE_STATSX ; 
 int CLUSTER_MODE_SUPPORT ; 
 int CLUSTER_MODE_TARG ; 
 int CLUSTER_MODE_TEMP ; 
 int CLUSTER_MODE_TEXT ; 
 int CLUSTER_MODE_WATCHCAT ; 
 scalar_t__ MAX_CONNECTIONS ; 
 int /*<<< orphan*/  MAX_PING_INTERVAL ; 
 int /*<<< orphan*/  MIN_PING_INTERVAL ; 
 int /*<<< orphan*/  aes_load_pwd_file (char*) ; 
 char* aes_pwd_file ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atof (void*) ; 
 void* atoi (void*) ; 
 void* backlog ; 
 char* config_filename ; 
 int daemonize ; 
 int default_cluster_mode ; 
 scalar_t__ default_max_connections ; 
 scalar_t__ default_min_connections ; 
 int do_reload_config (int /*<<< orphan*/ ) ; 
 long long dynamic_data_buffer_size ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  extension_name ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 void* logname ; 
 scalar_t__ maxconn ; 
 int /*<<< orphan*/  nice (void*) ; 
 int /*<<< orphan*/  only_first_cluster ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  ping_interval ; 
 void* port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int sscanf (void*,char*,long long*,char*) ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (void*,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 void* username ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int main (int argc, char *argv[]) {
  int i;
  long long x;
  char c;

  set_debug_handlers ();

  progname = argv[0];
  char *custom_encr = 0;
  while ((i = getopt (argc, argv, "b:c:l:p:n:dhu:vfFP:X:E:H:T:y:z:")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'F':
      default_cluster_mode++;
      break;
    case 'f':
      only_first_cluster++;
      break;
    case 'h':
      usage();
      return 2;
    case 'b':
      backlog = atoi(optarg);
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
    case 'y':
      i = atoi (optarg);
      if (i >= 1 && i <= 1000) {
	default_min_connections = i;
      }
      break;
    case 'z':
      i = atoi (optarg);
      if (i >= 1 && i <= 1000) {
	default_max_connections = i;
      }
      break;
    case 'p':
      port = atoi (optarg);
      break;
    case 'n':
      errno = 0;
      nice (atoi (optarg));
      if (errno) {
        perror ("nice");
      }
      break;
    case 'u':
      username = optarg;
      break;
    case 'l':
      logname = optarg;
      break;
    case 'P':
      aes_pwd_file = optarg;
      break;
    case 'X':
      strncpy (extension_name, optarg, 15);
      if (!strcmp (optarg, "text")) {
        default_cluster_mode |= CLUSTER_MODE_TEXT;
      } else if (!strcmp (optarg, "lists")) {
        default_cluster_mode |= CLUSTER_MODE_LISTS;
      } else if (!strcmp (optarg, "hints")) {
        default_cluster_mode |= CLUSTER_MODE_HINTS;
      } else if (!strcmp (optarg, "logs")) {
        default_cluster_mode |= CLUSTER_MODE_LOGS;
      } else if (!strcmp (optarg, "magus")) {
        default_cluster_mode |= CLUSTER_MODE_MAGUS;
      } else if (!strcmp (optarg, "news")) {
        default_cluster_mode |= CLUSTER_MODE_NEWS;
      } else if (!strcmp (optarg, "roundrobin")) {
        default_cluster_mode |= CLUSTER_MODE_ROUNDROBIN;
      } else if (!strcmp (optarg, "bayes")) {
        default_cluster_mode |= CLUSTER_MODE_BAYES;
      } else if (!strcmp (optarg, "antispam")) {
        default_cluster_mode |= CLUSTER_MODE_ANTISPAM;
      } else if (!strcmp (optarg, "temp")) {
        default_cluster_mode |= CLUSTER_MODE_TEMP;
      } else if (!strcmp (optarg, "support")) {
        default_cluster_mode |= CLUSTER_MODE_SUPPORT;
      } else if (!strcmp (optarg, "photo")) {
        default_cluster_mode |= CLUSTER_MODE_PHOTO;
      } else if (!strcmp (optarg, "dot")) {
        default_cluster_mode |= CLUSTER_MODE_DOT;
      } else if (!strcmp (optarg, "search")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_SEARCH;
      } else if (!strcmp (optarg, "targ")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_TARG;
      } else if (!strcmp (optarg, "news_ug")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_NEWS_UG;
      } else if (!strcmp (optarg, "news_g")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_NEWS_G;
      } else if (!strcmp (optarg, "news_comm")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_NEWS_COMM;
      } else if (!strcmp (optarg, "newsr")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_NEWSR;
      } else if (!strcmp (optarg, "statsx")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_STATSX;
      } else if (!strcmp (optarg, "friends")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_FRIENDS;
      } else if (!strcmp (optarg, "searchx")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_SEARCHX;
      } else if (!strcmp (optarg, "watchcat")) {
        default_cluster_mode |= CLUSTER_MODE_WATCHCAT;
      } else if (!strcmp (optarg, "hints_merge")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_HINTS_MERGE;
      } else if (!strcmp (optarg, "random_merge")) {
        if (default_cluster_mode & CLUSTER_MODE_MERGE) {
          fprintf (stderr, "Can not enable to merge extensions");
          return 2;
        }
        default_cluster_mode |= CLUSTER_MODE_RANDOM_MERGE;
      } else {
        usage ();
        return 2;
      }
      break;
    case 'T':
      ping_interval = atof (optarg);
      if (ping_interval < MIN_PING_INTERVAL || ping_interval > MAX_PING_INTERVAL) {
	usage ();
	return 2;
      }
      break;
    case 'E':
      custom_encr = optarg;
      break;
    case 'd':
      daemonize ^= 1;
      break;
    case 'H':
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
    }
  }
  if (argc != optind + 1) {
    usage();
    return 2;
  }

  if (default_max_connections < default_min_connections) {
    kprintf ("WARNING: adjusted default maximum number of connections to be equal to default minimum number of connections\n");
    default_max_connections = default_min_connections;
  }

  init_dyn_data ();

  if (raise_file_rlimit (maxconn + 16) < 0) {
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

  if (custom_encr) {
    aes_load_pwd_file (custom_encr);
  } else {
    aes_load_pwd_file (aes_pwd_file);
  }

  start_time = time (0);

  start_server ();

  return 0;
}