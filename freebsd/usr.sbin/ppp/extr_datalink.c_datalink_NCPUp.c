#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  authname; } ;
struct datalink {TYPE_4__* physical; TYPE_2__* parent; TYPE_11__* bundle; TYPE_1__ peer; int /*<<< orphan*/  name; } ;
struct TYPE_24__ {int /*<<< orphan*/  open_mode; } ;
struct TYPE_23__ {TYPE_1__ peer; } ;
struct TYPE_19__ {int /*<<< orphan*/  fsm; scalar_t__ his_mrru; scalar_t__ want_mrru; } ;
struct TYPE_15__ {TYPE_8__ fsm; } ;
struct TYPE_22__ {TYPE_3__ lcp; TYPE_10__ ccp; } ;
struct TYPE_21__ {TYPE_7__ mp; } ;
struct TYPE_20__ {TYPE_6__ link; } ;
struct TYPE_18__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerUp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {TYPE_5__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATALINK_OPEN ; 
 int /*<<< orphan*/  LogPHASE ; 
#define  MP_ADDED 131 
#define  MP_FAILED 130 
#define  MP_LINKSENT 129 
#define  MP_UP 128 
 int /*<<< orphan*/  OPEN_PASSIVE ; 
 scalar_t__ PHASE_NETWORK ; 
 int /*<<< orphan*/  auth_Select (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_CalculateBandwidth (TYPE_11__*) ; 
 int /*<<< orphan*/  bundle_NewPhase (TYPE_11__*,scalar_t__) ; 
 scalar_t__ bundle_Phase (TYPE_11__*) ; 
 int ccp_SetOpenMode (TYPE_10__*) ; 
 int /*<<< orphan*/  datalink_AuthNotOk (struct datalink*) ; 
 int /*<<< orphan*/  datalink_NewState (struct datalink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_Open (TYPE_8__*) ; 
 int /*<<< orphan*/  fsm_Up (TYPE_8__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mp_Up (TYPE_7__*,struct datalink*) ; 
 int /*<<< orphan*/  ncp_SetLink (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
datalink_NCPUp(struct datalink *dl)
{
  int ccpok = ccp_SetOpenMode(&dl->physical->link.ccp);

  if (dl->physical->link.lcp.want_mrru && dl->physical->link.lcp.his_mrru) {
    /* we've authenticated in multilink mode ! */
    switch (mp_Up(&dl->bundle->ncp.mp, dl)) {
      case MP_LINKSENT:
        /* We've handed the link off to another ppp (well, we will soon) ! */
        return;
      case MP_UP:
        /* First link in the bundle */
        auth_Select(dl->bundle, dl->peer.authname);
        bundle_CalculateBandwidth(dl->bundle);
        /* FALLTHROUGH */
      case MP_ADDED:
        /* We're in multilink mode ! */
        dl->physical->link.ccp.fsm.open_mode = OPEN_PASSIVE;	/* override */
        bundle_CalculateBandwidth(dl->bundle);
        break;
      case MP_FAILED:
        datalink_AuthNotOk(dl);
        return;
    }
  } else if (bundle_Phase(dl->bundle) == PHASE_NETWORK) {
    log_Printf(LogPHASE, "%s: Already in NETWORK phase\n", dl->name);
    datalink_NewState(dl, DATALINK_OPEN);
    bundle_CalculateBandwidth(dl->bundle);
    (*dl->parent->LayerUp)(dl->parent->object, &dl->physical->link.lcp.fsm);
    return;
  } else {
    dl->bundle->ncp.mp.peer = dl->peer;
    ncp_SetLink(&dl->bundle->ncp, &dl->physical->link);
    auth_Select(dl->bundle, dl->peer.authname);
  }

  if (ccpok) {
    fsm_Up(&dl->physical->link.ccp.fsm);
    fsm_Open(&dl->physical->link.ccp.fsm);
  }
  datalink_NewState(dl, DATALINK_OPEN);
  bundle_NewPhase(dl->bundle, PHASE_NETWORK);
  (*dl->parent->LayerUp)(dl->parent->object, &dl->physical->link.lcp.fsm);
}