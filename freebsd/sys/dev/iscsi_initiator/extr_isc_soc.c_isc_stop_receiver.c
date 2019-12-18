#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * soc; int /*<<< orphan*/  td; int /*<<< orphan*/  io_mtx; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int ISC_CON_RUN ; 
 int ISC_CON_RUNNING ; 
 int ISC_LINK_UP ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  SHUT_RD ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  fdrop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug (int,char*,...) ; 
 int /*<<< orphan*/  soshutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isc_stop_receiver(isc_session_t *sp)
{
     int	n;

     debug_called(8);
     sdebug(3, "sp=%p sp->soc=%p", sp, sp? sp->soc: 0);
     mtx_lock(&sp->io_mtx);
     sp->flags &= ~ISC_LINK_UP;
     msleep(&sp->soc, &sp->io_mtx, PRIBIO|PDROP, "isc_stpc", 5*hz);

     soshutdown(sp->soc, SHUT_RD);

     mtx_lock(&sp->io_mtx);
     sdebug(3, "soshutdown");
     sp->flags &= ~ISC_CON_RUN;
     n = 2;
     while(n-- && (sp->flags & ISC_CON_RUNNING)) {
	  sdebug(3, "waiting n=%d... flags=%x", n, sp->flags);
	  msleep(&sp->soc, &sp->io_mtx, PRIBIO, "isc_stpc", 5*hz);
     }
     mtx_unlock(&sp->io_mtx);

     if(sp->fp != NULL)
	  fdrop(sp->fp, sp->td);
     sp->soc = NULL;
     sp->fp = NULL;

     sdebug(3, "done");
}