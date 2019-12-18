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
 void* atoi (void*) ; 
 void* backlog ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int daemonize ; 
 int /*<<< orphan*/  exit (int) ; 
 void* logname ; 
 void* maxconn ; 
 void* optarg ; 
 void* port ; 
 int /*<<< orphan*/  usage () ; 
 void* username ; 
 int /*<<< orphan*/  verbosity ; 

int process_engine_option (int opt) {
  switch (opt) {      
  case 'v':
    verbosity++;
    break;
  case 'h':
    usage ();
    return 2;
  case 'b':
    backlog = atoi (optarg);
    if (backlog <= 0) backlog = BACKLOG;
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
  case 'u':
    username = optarg;
    break;
  case 'l':
    logname = optarg;
    break;
  case 'd':
    daemonize ^= 1;
    break;
  case 'r':
    binlog_disabled++;
    break;
  default:
    usage ();
    exit (1);
  }
  return 0;
}