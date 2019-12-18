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
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 void* backlog ; 
 int daemonize ; 
 int /*<<< orphan*/  init_logname (int /*<<< orphan*/ ) ; 
 int max_memory ; 
 void* maxconn ; 
 int /*<<< orphan*/  mlockall (int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  username ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int main_args_default_handler (int i) {
  switch (i) {
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
  case 'l':
    init_logname (optarg);
    break;
  case 'm':
    max_memory = atoi (optarg);
    if (max_memory < 1) {
      max_memory = 1;
    }
    if (max_memory > 2047) {
      max_memory = 2047;
    }
    max_memory *= 1048576;
    break;
  case 'u':
    username = optarg;
    break;
  case 'd':
    daemonize ^= 1;
    break;
  case 'h':
    usage();
    return 2;
  case 'k':
    if (mlockall (MCL_CURRENT | MCL_FUTURE) != 0) {
      vkprintf (-1, "error: fail to lock paged memory\n");
    }
    break;
  case 'v':
    verbosity++;
    break;
  default:
    return 0;
  }
  return 1;
}