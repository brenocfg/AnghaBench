#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* name; int load; void* arg; int /*<<< orphan*/  func; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* req ) (struct authinfo*) ;} ;
struct TYPE_6__ {int timeout; int /*<<< orphan*/  maxreq; } ;
struct TYPE_7__ {TYPE_1__ fsm; } ;
struct authinfo {int id; TYPE_4__ authtimer; TYPE_3__ fn; TYPE_2__ cfg; int /*<<< orphan*/  retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  AuthTimeout ; 
 int SECTICKS ; 
 int /*<<< orphan*/  stub1 (struct authinfo*) ; 
 int /*<<< orphan*/  timer_Start (TYPE_4__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_4__*) ; 

void
auth_StartReq(struct authinfo *authp)
{
  timer_Stop(&authp->authtimer);
  authp->authtimer.func = AuthTimeout;
  authp->authtimer.name = "auth";
  authp->authtimer.load = authp->cfg.fsm.timeout * SECTICKS;
  authp->authtimer.arg = (void *)authp;
  authp->retry = authp->cfg.fsm.maxreq;
  authp->id = 1;
  (*authp->fn.req)(authp);
  timer_Start(&authp->authtimer);
}