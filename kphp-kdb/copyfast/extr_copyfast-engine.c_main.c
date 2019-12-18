#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct hostent {scalar_t__ h_addrtype; int h_length; scalar_t__ h_addr; int /*<<< orphan*/  h_addr_list; } ;
struct TYPE_5__ {void* port; } ;
struct TYPE_4__ {void* port; struct in_addr target; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ MAX_CONNECTIONS ; 
 TYPE_3__ PID ; 
 int /*<<< orphan*/  add_cluster (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_load_pwd_file (char*) ; 
 void* atoi (void*) ; 
 int /*<<< orphan*/  create_target (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int daemonize ; 
 TYPE_1__ default_ct ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct hostent* gethostbyname (char*) ; 
 int getopt (int,char**,char*) ; 
 char* hostname ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 void* logname ; 
 int /*<<< orphan*/  main_targ ; 
 scalar_t__ maxconn ; 
 void* optarg ; 
 int optind ; 
 void* port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 int /*<<< orphan*/  read_network_file (char*) ; 
 void* server_port ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (char*,void*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 void* username ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  int i;

  set_debug_handlers ();

  progname = argv[0];

  char encr_file[256];
  char network_desc_file[256];
  int custom_encr = 0;


  while ((i = getopt (argc, argv, "vdc:a:p:E:P:N:u:l:")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'c':
      maxconn = atoi(optarg);
      if (maxconn <= 0 || maxconn > MAX_CONNECTIONS) {
        maxconn = MAX_CONNECTIONS;
      }
      break;
    case 'a':
      strncpy (hostname, optarg, 255);
      break;
    case 'p':
      port = atoi(optarg);
      break;
    case 'P':
      server_port = atoi(optarg);
      break;
    case 'E':
      strncpy (encr_file, optarg, 255);
      custom_encr = 1;
      break;
    case 'N':
      strncpy (network_desc_file, optarg, 255);
      break;
    case 'u':
      username = optarg;
      break;
    case 'l':
      logname = optarg;
      break;
    case 'h':
      usage ();
      return 2;
    case 'd':
      daemonize ^= 1;
    }
  }
  
  PID.port = port;

  if (argc <= optind) {
    usage();
    return 2;
  }




  if (raise_file_rlimit(maxconn + 16) < 0) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit(1);
  }

  if (!custom_encr) {
    aes_load_pwd_file (0);
  } else {
    aes_load_pwd_file (encr_file);
  }

  init_dyn_data();

  for (i = optind; i < argc; i++) {
    add_cluster (0, 0, argv[i], 0);
  }

  read_network_file (network_desc_file);

  start_time = time(0);
  
  struct hostent *h;
  if (!(h = gethostbyname (hostname)) || h->h_addrtype != AF_INET || h->h_length != 4 || !h->h_addr_list || !h->h_addr) {
    fprintf (stderr, "cannot resolve %s\n", hostname);
    exit (2);
  }
  default_ct.target = *((struct in_addr *) h->h_addr);
  default_ct.port = server_port;

  main_targ = create_target (&default_ct, 0);

  start_server();

  return 0;
}