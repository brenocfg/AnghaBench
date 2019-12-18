#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int /*<<< orphan*/  rq_xprt; } ;
struct sockaddr {int dummy; } ;
struct sm_stat_res {int /*<<< orphan*/  state; void* res_stat; } ;
struct addrinfo {int dummy; } ;
typedef  struct sm_stat_res sm_stat_res ;
struct TYPE_5__ {int /*<<< orphan*/  mon_name; } ;
typedef  TYPE_1__ sm_name ;
struct TYPE_7__ {int /*<<< orphan*/  ourState; } ;
struct TYPE_6__ {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  from_addr (struct sockaddr*) ; 
 scalar_t__ getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int sm_check_hostname (struct svc_req*,int /*<<< orphan*/ ) ; 
 void* stat_fail ; 
 void* stat_succ ; 
 TYPE_3__* status_info ; 
 TYPE_2__* svc_getrpccaller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

struct sm_stat_res *sm_stat_1_svc(sm_name *arg, struct svc_req *req)
{
  static sm_stat_res res;
  struct addrinfo *ai;
  struct sockaddr *claddr;
  static int err;

  err = 1;
  if ((err = sm_check_hostname(req, arg->mon_name)) == 0)
  {
    res.res_stat = stat_fail;
  }
  if (err != 0)
  {
    if (debug)
	    syslog(LOG_DEBUG, "stat called for host %s", arg->mon_name);
    if (getaddrinfo(arg->mon_name, NULL, NULL, &ai) == 0) {
	    res.res_stat = stat_succ;
	    freeaddrinfo(ai);
    }
    else
    {
      claddr = (struct sockaddr *) (svc_getrpccaller(req->rq_xprt)->buf) ;
      syslog(LOG_ERR, "invalid hostname to sm_stat from %s: %s",
	  from_addr(claddr), arg->mon_name);
      res.res_stat = stat_fail;
    }
  }
  res.state = status_info->ourState;
  return (&res);
}