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
 void* atoi (void*) ; 
 void* backlog ; 
 char* config_filename ; 
 int daemonize ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 void* logname ; 
 scalar_t__ maxconn ; 
 int /*<<< orphan*/  open_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  parse_config () ; 
 int port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 scalar_t__ sdf ; 
 scalar_t__ server_socket (int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settings_addr ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 void* username ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  int i;

  progname = argv[0];
  while ((i = getopt (argc, argv, "b:c:l:p:dhu:v")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'h':
      usage();
      return 2;
    case 'b':
      backlog = atoi(optarg);
      if (backlog <= 0) backlog = BACKLOG;
      break;
    case 'c':
      maxconn = atoi(optarg);
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
    case 'd':
      daemonize ^= 1;
    }
  }
  if (argc != optind + 1) {
    usage();
    return 2;
  }

  open_file (0, config_filename = argv[optind], 0);
  parse_config ();

  if (raise_file_rlimit(maxconn + 16) < 0) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit(1);
  }

  sdf = server_socket (port, settings_addr, backlog, 0);
  if (sdf < 0) {
    fprintf(stderr, "cannot open server socket at port %d: %m\n", port);
    exit(1);
  }


  start_time = time(0);

  start_server();

  return 0;
}