#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  SESS_DISCONNECT ; 
 int /*<<< orphan*/  SESS_RECONNECT ; 
#define  SIGHUP 131 
#define  SIGINT 130 
#define  SIGTERM 129 
#define  SIGUSR1 128 
 TYPE_1__* currsess ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
trap(int sig)
{
     syslog(LOG_NOTICE, "trapped signal %d", sig);
     fprintf(stderr, "trapped signal %d\n", sig);

     switch(sig) {
     case SIGHUP:
	  currsess->flags |= SESS_DISCONNECT;
	  break;

     case SIGUSR1:
	  currsess->flags |= SESS_RECONNECT;
	  break;

     case SIGINT: 
     case SIGTERM:
     default:
	  return; // ignore
     }
}