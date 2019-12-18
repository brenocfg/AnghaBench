#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct sm_stat_res {void* res_stat; int /*<<< orphan*/  state; } ;
struct addrinfo {int dummy; } ;
typedef  struct sm_stat_res sm_stat_res ;
struct TYPE_9__ {int /*<<< orphan*/  my_proc; int /*<<< orphan*/  my_vers; int /*<<< orphan*/  my_prog; int /*<<< orphan*/  my_name; } ;
struct TYPE_10__ {TYPE_1__ my_id; int /*<<< orphan*/  mon_name; } ;
struct TYPE_11__ {int /*<<< orphan*/  priv; TYPE_2__ mon_id; } ;
typedef  TYPE_3__ mon ;
struct TYPE_14__ {int /*<<< orphan*/  ourState; } ;
struct TYPE_13__ {TYPE_4__* monList; } ;
struct TYPE_12__ {struct TYPE_12__* next; int /*<<< orphan*/  notifyData; int /*<<< orphan*/  notifyProc; int /*<<< orphan*/  notifyVers; int /*<<< orphan*/  notifyProg; int /*<<< orphan*/  notifyHost; } ;
typedef  TYPE_4__ MonList ;
typedef  TYPE_5__ HostInfo ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SM_MAXSTRLEN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ debug ; 
 TYPE_5__* find_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sm_check_hostname (struct svc_req*,int /*<<< orphan*/ ) ; 
 void* stat_fail ; 
 void* stat_succ ; 
 TYPE_6__* status_info ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_file () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

struct sm_stat_res *sm_mon_1_svc(mon *arg, struct svc_req *req)
{
  static sm_stat_res res;
  HostInfo *hp;
  static int err;
  MonList *lp;
  struct addrinfo *ai;

  if ((err = sm_check_hostname(req, arg->mon_id.mon_name)) == 0)
  {
    res.res_stat = stat_fail;
  }

  if (err != 0)
  {
    if (debug)
    {
      syslog(LOG_DEBUG, "monitor request for host %s", arg->mon_id.mon_name);
      syslog(LOG_DEBUG, "recall host: %s prog: %d ver: %d proc: %d",
      arg->mon_id.my_id.my_name,
      arg->mon_id.my_id.my_prog,
      arg->mon_id.my_id.my_vers,
      arg->mon_id.my_id.my_proc);
    }
    res.res_stat = stat_fail;  /* Assume fail until set otherwise      */
    res.state = status_info->ourState;
  
    /* Find existing host entry, or create one if not found            */
    /* If find_host() fails, it will have logged the error already.    */
    if (getaddrinfo(arg->mon_id.mon_name, NULL, NULL, &ai) != 0)
    {
      syslog(LOG_ERR, "Invalid hostname to sm_mon: %s", arg->mon_id.mon_name);
      return (&res);
    }
    freeaddrinfo(ai);
    if ((hp = find_host(arg->mon_id.mon_name, TRUE)))
    {
      lp = (MonList *)malloc(sizeof(MonList));
      if (!lp)
      {
        syslog(LOG_ERR, "Out of memory");
      }
      else
      {
        strncpy(lp->notifyHost, arg->mon_id.my_id.my_name, SM_MAXSTRLEN);
        lp->notifyProg = arg->mon_id.my_id.my_prog;
        lp->notifyVers = arg->mon_id.my_id.my_vers;
        lp->notifyProc = arg->mon_id.my_id.my_proc;
        memcpy(lp->notifyData, arg->priv, sizeof(lp->notifyData));

        lp->next = hp->monList;
        hp->monList = lp;
        sync_file();

        res.res_stat = stat_succ;      /* Report success                       */
      }
    }
  }
  return (&res);
}