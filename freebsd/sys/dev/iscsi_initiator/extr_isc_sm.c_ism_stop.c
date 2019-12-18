#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct isc_softc {int /*<<< orphan*/  isc_mtx; int /*<<< orphan*/  nsess; int /*<<< orphan*/  isc_sess; int /*<<< orphan*/  unit_sx; int /*<<< orphan*/  unit; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  clist; int /*<<< orphan*/  opt; int /*<<< orphan*/  io_mtx; int /*<<< orphan*/  snd_mtx; int /*<<< orphan*/  hld_mtx; int /*<<< orphan*/  rsv_mtx; int /*<<< orphan*/  rsp_mtx; int /*<<< orphan*/  dev; int /*<<< orphan*/  sid; struct isc_softc* isc; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int ISC_FFPHASE ; 
 int ISC_SM_RUN ; 
 int ISC_SM_RUNNING ; 
 int /*<<< orphan*/  M_ISCSI ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  i_freeopt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_pdu_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  ic_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_stop_receiver (TYPE_1__*) ; 
 int /*<<< orphan*/  iscsi_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug (int,char*,...) ; 
 int /*<<< orphan*/  sp_link ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsleep (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (int*) ; 
 int /*<<< orphan*/  xdebug (char*) ; 

void
ism_stop(isc_session_t *sp)
{
     struct isc_softc *sc = sp->isc;
     int	n;

     debug_called(8);
     sdebug(2, "terminating");
     /*
      | first stop the receiver
      */
     isc_stop_receiver(sp);
     /*
      | now stop the xmitter
      */
     n = 5;
     sp->flags &= ~ISC_SM_RUN;
     while(n-- && (sp->flags & ISC_SM_RUNNING)) {
	  sdebug(2, "n=%d", n);
	  wakeup(&sp->flags);
	  tsleep(sp, PRIBIO, "-", 5*hz);
     }
     sdebug(2, "final n=%d", n);
     sp->flags &= ~ISC_FFPHASE;
     
     iscsi_cleanup(sp);

     (void)i_pdu_flush(sp);

     ic_destroy(sp);

     sx_xlock(&sc->unit_sx);
     free_unr(sc->unit, sp->sid);
     sx_xunlock(&sc->unit_sx);

     mtx_lock(&sc->isc_mtx);
     TAILQ_REMOVE(&sc->isc_sess, sp, sp_link);
     sc->nsess--;
     mtx_unlock(&sc->isc_mtx);

#if __FreeBSD_version < 700000
     destroy_dev(sp->dev);
#endif

     mtx_destroy(&sp->rsp_mtx);
     mtx_destroy(&sp->rsv_mtx);
     mtx_destroy(&sp->hld_mtx);
     mtx_destroy(&sp->snd_mtx);
     mtx_destroy(&sp->io_mtx);

     i_freeopt(&sp->opt);

     if(sysctl_ctx_free(&sp->clist))
	  xdebug("sysctl_ctx_free failed");

     free(sp, M_ISCSI);
}