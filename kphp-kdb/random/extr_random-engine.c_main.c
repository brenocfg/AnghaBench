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
 void* MAX_CONNECTIONS ; 
 int /*<<< orphan*/  PASSWORD_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atoi (void*) ; 
 void* backlog ; 
 int daemonize ; 
 int /*<<< orphan*/  engine_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 void* logname ; 
 void* maxconn ; 
 void* optarg ; 
 int optind ; 
 char* password_filename ; 
 void* port ; 
 char* progname ; 
 int /*<<< orphan*/  random_engine ; 
 int /*<<< orphan*/  random_init (int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int sscanf (void*,char*,long long*,char*) ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 void* username ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  char c;
  long long x;
  int i, key_len = 2048, buffer_size = 0;

  set_debug_handlers ();
  daemonize = 1;

  progname = argv[0];
  while ((i = getopt (argc, argv, "N:b:c:dhl:p:s:u:v")) != -1) {
    switch (i) {
    case 'N':
      key_len = atoi (optarg);
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
    case 'd':
      daemonize ^= 1;
      break;
    case 'h':
      usage ();
      break;
    case 'l':
      logname = optarg;
      break;
    case 'v':
      verbosity++;
      break;
    case 'p':
      port = atoi (optarg);
      break;
    case 's':
       c = 0;
       assert (sscanf (optarg, "%lld%c", &x, &c) >= 1);
       switch (c | 0x20) {
         case 'k':  x <<= 10; break;
         case 'm':  x <<= 20; break;
         case 'g':  x <<= 30; break;
         case 't':  x <<= 40; break;
         default: assert (c == 0x20);
       }
       if (x >= 1024 && x < (1LL << 30)) {
         buffer_size = x;
       }
      break;
    case 'u':
      username = optarg;
      break;
    }
  }

  if (optind + 1 != argc) {
    kprintf ("<password-file> wasn't given\n");
    usage ();
  }

  password_filename = argv[optind];

  engine_init (&random_engine, 0, 0);

  start_time = time (0);

  random_init (2048, buffer_size, password_filename, PASSWORD_LENGTH);

  start_server ();
  return 0;
}