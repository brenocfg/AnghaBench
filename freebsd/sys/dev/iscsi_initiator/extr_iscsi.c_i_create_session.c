#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct isc_softc {int /*<<< orphan*/  isc_mtx; int /*<<< orphan*/  isc_sess; int /*<<< orphan*/  unit_sx; int /*<<< orphan*/  unit; } ;
struct cdev {struct isc_softc* si_drv1; } ;
struct TYPE_9__ {int maxRecvDataSegmentLength; int maxXmitDataSegmentLength; int maxBurstLength; int /*<<< orphan*/  maxluns; } ;
struct TYPE_10__ {int sid; TYPE_1__ opt; TYPE_4__* dev; struct isc_softc* isc; } ;
typedef  TYPE_2__ isc_session_t ;
struct TYPE_12__ {int /*<<< orphan*/  nsess; } ;
struct TYPE_11__ {TYPE_2__* si_drv2; struct isc_softc* si_drv1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  ISCSI_MAX_LUNS ; 
 int /*<<< orphan*/  M_ISCSI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* isc ; 
 int /*<<< orphan*/  iscsi_cdevsw ; 
 int ism_start (TYPE_2__*) ; 
 TYPE_4__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sp_link ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdebug (char*) ; 

__attribute__((used)) static int
i_create_session(struct cdev *dev, int *ndev)
{ 
     struct isc_softc	*sc = dev->si_drv1;
     isc_session_t	*sp;
     int		error, n;

     debug_called(8);

     sp = malloc(sizeof(isc_session_t), M_ISCSI, M_WAITOK | M_ZERO);
     if(sp == NULL)
	  return ENOMEM;

     sx_xlock(&sc->unit_sx);
     if((n = alloc_unr(sc->unit)) < 0) {
	  sx_unlock(&sc->unit_sx);
	  free(sp, M_ISCSI);
	  xdebug("too many sessions!");
	  return EPERM;
     }
     sx_unlock(&sc->unit_sx);

     mtx_lock(&sc->isc_mtx);
     TAILQ_INSERT_TAIL(&sc->isc_sess, sp, sp_link);
     isc->nsess++;
     mtx_unlock(&sc->isc_mtx);

     sp->dev = make_dev(&iscsi_cdevsw, n, UID_ROOT, GID_WHEEL, 0600, "iscsi%d", n);
     *ndev = sp->sid = n;
     sp->isc = sc;
     sp->dev->si_drv1 = sc;
     sp->dev->si_drv2 = sp;

     sp->opt.maxRecvDataSegmentLength = 8192;
     sp->opt.maxXmitDataSegmentLength = 8192;
     sp->opt.maxBurstLength = 65536;	// 64k
     sp->opt.maxluns = ISCSI_MAX_LUNS;

     error = ism_start(sp);

     return error;
}