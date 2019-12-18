#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_4__ {int noOfHosts; TYPE_1__* hosts; } ;
struct TYPE_3__ {int notifyReqd; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ HostInfo ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int TRUE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 scalar_t__ notify_one_host (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 TYPE_2__* status_info ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_file () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void notify_hosts(void)
{
  int i;
  int attempts;
  int work_to_do = FALSE;
  HostInfo *hp;
  pid_t pid;

  /* First check if there is in fact any work to do.			*/
  for (i = status_info->noOfHosts, hp = status_info->hosts; i ; i--, hp++)
  {
    if (hp->notifyReqd)
    {
      work_to_do = TRUE;
      break;
    }
  }

  if (!work_to_do) return;	/* No work found			*/

  pid = fork();
  if (pid == -1)
  {
    syslog(LOG_ERR, "Unable to fork notify process - %s", strerror(errno));
    return;
  }
  if (pid) return;

  /* Here in the child process.  We continue until all the hosts marked	*/
  /* as requiring notification have been duly notified.			*/
  /* If one of the initial attempts fails, we sleep for a while and	*/
  /* have another go.  This is necessary because when we have crashed,	*/
  /* (eg. a power outage) it is quite possible that we won't be able to	*/
  /* contact all monitored hosts immediately on restart, either because	*/
  /* they crashed too and take longer to come up (in which case the	*/
  /* notification isn't really required), or more importantly if some	*/
  /* router etc. needed to reach the monitored host has not come back	*/
  /* up yet.  In this case, we will be a bit late in re-establishing	*/
  /* locks (after the grace period) but that is the best we can do.	*/
  /* We try 10 times at 5 sec intervals, 10 more times at 1 minute	*/
  /* intervals, then 24 more times at hourly intervals, finally		*/
  /* giving up altogether if the host hasn't come back to life after	*/
  /* 24 hours.								*/

  for (attempts = 0; attempts < 44; attempts++)
  {
    work_to_do = FALSE;		/* Unless anything fails		*/
    for (i = status_info->noOfHosts, hp = status_info->hosts; i ; i--, hp++)
    {
      if (hp->notifyReqd)
      {
        if (notify_one_host(hp->hostname, attempts == 0))
	{
	  hp->notifyReqd = FALSE;
          sync_file();
	}
	else work_to_do = TRUE;
      }
    }
    if (!work_to_do) break;
    if (attempts < 10) sleep(5);
    else if (attempts < 20) sleep(60);
    else sleep(60*60);
  }
  exit(0);
}