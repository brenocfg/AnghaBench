#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  stp; int /*<<< orphan*/  flags; int /*<<< orphan*/  io_mtx; int /*<<< orphan*/  hld_mtx; int /*<<< orphan*/  snd_mtx; int /*<<< orphan*/  rsp_mtx; int /*<<< orphan*/  rsv_mtx; int /*<<< orphan*/  hld; int /*<<< orphan*/  wsnd; int /*<<< orphan*/  isnd; int /*<<< orphan*/  csnd; int /*<<< orphan*/  rsv; int /*<<< orphan*/  rsp; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_SM_RUN ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  isc_add_sysctls (TYPE_1__*) ; 
 int /*<<< orphan*/  ism_out ; 
 int kproc_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int kthread_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ism_start(isc_session_t *sp)
{
     debug_called(8);
    /*
     | now is a good time to do some initialization
     */
     TAILQ_INIT(&sp->rsp);
     TAILQ_INIT(&sp->rsv);
     TAILQ_INIT(&sp->csnd);
     TAILQ_INIT(&sp->isnd);
     TAILQ_INIT(&sp->wsnd);
     TAILQ_INIT(&sp->hld);

     mtx_init(&sp->rsv_mtx, "iscsi-rsv", NULL, MTX_DEF);
     mtx_init(&sp->rsp_mtx, "iscsi-rsp", NULL, MTX_DEF);
     mtx_init(&sp->snd_mtx, "iscsi-snd", NULL, MTX_DEF);
     mtx_init(&sp->hld_mtx, "iscsi-hld", NULL, MTX_DEF);
     mtx_init(&sp->io_mtx, "iscsi-io", NULL, MTX_DEF);

     isc_add_sysctls(sp);

     sp->flags |= ISC_SM_RUN;

     debug(4, "starting ism_proc: sp->sid=%d", sp->sid);

#if __FreeBSD_version >= 800000
     return kproc_create(ism_out, sp, &sp->stp, 0, 0, "isc_out %d", sp->sid);
#else
     return kthread_create(ism_out, sp, &sp->stp, 0, 0, "isc_out %d", sp->sid);
#endif
}