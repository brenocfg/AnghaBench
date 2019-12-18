#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct isc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  pduq_t ;
struct TYPE_5__ {TYPE_1__* si_drv1; } ;
struct TYPE_4__ {TYPE_2__* dev; int /*<<< orphan*/  nsess; int /*<<< orphan*/  oid; int /*<<< orphan*/  clist; int /*<<< orphan*/ * eh; int /*<<< orphan*/  unit_sx; int /*<<< orphan*/  unit; int /*<<< orphan*/  pdu_zone; int /*<<< orphan*/  isc_sess; int /*<<< orphan*/  isc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int EEXIST ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_CHECKNAME ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_ISCSI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 scalar_t__ SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  _net ; 
 int /*<<< orphan*/  debug_called (int) ; 
 TYPE_1__* isc ; 
 int /*<<< orphan*/  iscsi_cdevsw ; 
 int /*<<< orphan*/  iscsi_dbg_mtx ; 
 char* iscsi_driver_version ; 
 int /*<<< orphan*/  iscsi_shutdown ; 
 char* isid ; 
 TYPE_2__* make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_pdus ; 
 scalar_t__ max_sessions ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sc ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdebug (char*) ; 

__attribute__((used)) static int
iscsi_start(void)
{
     debug_called(8);

     isc =  malloc(sizeof(struct isc_softc), M_ISCSI, M_ZERO|M_WAITOK);
     mtx_init(&isc->isc_mtx, "iscsi-isc", NULL, MTX_DEF);

     TAILQ_INIT(&isc->isc_sess);
     /*
      | now init the free pdu list
      */
     isc->pdu_zone = uma_zcreate("pdu", sizeof(pduq_t),
				 NULL, NULL, NULL, NULL,
				 0, 0);
     uma_zone_set_max(isc->pdu_zone, max_pdus);
     isc->unit = new_unrhdr(0, max_sessions-1, NULL);
     sx_init(&isc->unit_sx, "iscsi sx");

#ifdef DO_EVENTHANDLER
     if((isc->eh = EVENTHANDLER_REGISTER(shutdown_pre_sync, iscsi_shutdown,
					sc, SHUTDOWN_PRI_DEFAULT-1)) == NULL)
	  xdebug("shutdown event registration failed\n");
#endif
     /*
      | sysctl stuff
      */
     sysctl_ctx_init(&isc->clist);
     isc->oid = SYSCTL_ADD_NODE(&isc->clist,
			       SYSCTL_STATIC_CHILDREN(_net),
			       OID_AUTO,
			       "iscsi_initiator",
			       CTLFLAG_RD,
			       0,
			       "iSCSI Subsystem");

     SYSCTL_ADD_STRING(&isc->clist,
		       SYSCTL_CHILDREN(isc->oid),
		       OID_AUTO,
		       "driver_version",
		       CTLFLAG_RD,
		       iscsi_driver_version,
		       0,
		       "iscsi driver version");
 
     SYSCTL_ADD_STRING(&isc->clist,
		       SYSCTL_CHILDREN(isc->oid),
		       OID_AUTO,
		       "isid",
		       CTLFLAG_RW,
		       isid,
		       6+1,
		       "initiator part of the Session Identifier");

     SYSCTL_ADD_INT(&isc->clist,
		    SYSCTL_CHILDREN(isc->oid),
		    OID_AUTO,
		    "sessions",
		    CTLFLAG_RD,
		    &isc->nsess,
		    sizeof(isc->nsess),
		    "number of active session");

#ifdef ISCSI_INITIATOR_DEBUG
     mtx_init(&iscsi_dbg_mtx, "iscsi_dbg", NULL, MTX_DEF);
#endif

     isc->dev = make_dev_credf(MAKEDEV_CHECKNAME, &iscsi_cdevsw, max_sessions,
			       NULL, UID_ROOT, GID_WHEEL, 0600, "iscsi");
     if (isc->dev == NULL) {
	  xdebug("iscsi_initiator: make_dev_credf failed");
	  return (EEXIST);
     }
     isc->dev->si_drv1 = isc;

     printf("iscsi: version %s\n", iscsi_driver_version);
     return (0);
}