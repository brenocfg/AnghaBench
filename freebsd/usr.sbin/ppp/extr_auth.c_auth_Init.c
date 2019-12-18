#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct physical {int dummy; } ;
struct TYPE_4__ {void* failure; void* success; void* req; } ;
struct TYPE_6__ {scalar_t__ maxtrm; int /*<<< orphan*/  maxreq; int /*<<< orphan*/  timeout; } ;
struct TYPE_5__ {TYPE_3__ fsm; } ;
struct authinfo {struct physical* physical; TYPE_1__ fn; TYPE_2__ cfg; } ;
typedef  void* auth_func ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FSMAUTHTRIES ; 
 int /*<<< orphan*/  DEF_FSMRETRY ; 
 int /*<<< orphan*/  memset (struct authinfo*,char,int) ; 

void
auth_Init(struct authinfo *authp, struct physical *p, auth_func req,
          auth_func success, auth_func failure)
{
  memset(authp, '\0', sizeof(struct authinfo));
  authp->cfg.fsm.timeout = DEF_FSMRETRY;
  authp->cfg.fsm.maxreq = DEF_FSMAUTHTRIES;
  authp->cfg.fsm.maxtrm = 0;	/* not used */
  authp->fn.req = req;
  authp->fn.success = success;
  authp->fn.failure = failure;
  authp->physical = p;
}