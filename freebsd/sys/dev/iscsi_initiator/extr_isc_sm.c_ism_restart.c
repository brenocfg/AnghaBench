#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cmd; } ;
struct TYPE_6__ {int flags; TYPE_1__ sn; int /*<<< orphan*/  io_mtx; } ;
typedef  TYPE_2__ isc_session_t ;

/* Variables and functions */
 int ISC_OWAITING ; 
 int iscsi_requeue (TYPE_2__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug (int,char*,...) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
ism_restart(isc_session_t *sp)
{
     int lastcmd;

     sdebug(2, "restart ...");
     lastcmd = iscsi_requeue(sp);
#if 0
     if(lastcmd != sp->sn.cmd) {
	  sdebug(1, "resetting CmdSN to=%d (from %d)", lastcmd, sp->sn.cmd);
	  sp->sn.cmd = lastcmd;
     }
#endif
     mtx_lock(&sp->io_mtx);
     if(sp->flags & ISC_OWAITING) {
	  wakeup(&sp->flags);
     }
     mtx_unlock(&sp->io_mtx);

     sdebug(2, "restarted sn.cmd=0x%x lastcmd=0x%x", sp->sn.cmd, lastcmd);
}