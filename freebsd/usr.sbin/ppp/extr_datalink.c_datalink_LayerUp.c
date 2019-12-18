#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lcp {scalar_t__ auth_ineed; scalar_t__ want_auth; scalar_t__ auth_iwait; scalar_t__ his_auth; int /*<<< orphan*/  want_authtype; int /*<<< orphan*/  his_authtype; } ;
struct fsm {scalar_t__ proto; } ;
struct TYPE_6__ {int /*<<< orphan*/  auth; } ;
struct datalink {TYPE_5__* physical; TYPE_2__* parent; TYPE_1__ chap; int /*<<< orphan*/  pap; int /*<<< orphan*/  name; int /*<<< orphan*/  bundle; } ;
struct TYPE_8__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_9__ {TYPE_3__ ccp; struct lcp lcp; } ;
struct TYPE_10__ {TYPE_4__ link; } ;
struct TYPE_7__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerUp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Auth2Nam (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  PHASE_AUTHENTICATE ; 
 scalar_t__ PHASE_NETWORK ; 
 scalar_t__ PROTO_CCP ; 
 scalar_t__ PROTO_CHAP ; 
 scalar_t__ PROTO_LCP ; 
 scalar_t__ PROTO_PAP ; 
 int /*<<< orphan*/  auth_StartReq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bundle_NewPhase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bundle_Phase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datalink_AuthOk (struct datalink*) ; 
 int /*<<< orphan*/  datalink_GotAuthname (struct datalink*,char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
datalink_LayerUp(void *v, struct fsm *fp)
{
  /* The given fsm is now up */
  struct datalink *dl = (struct datalink *)v;
  struct lcp *lcp = &dl->physical->link.lcp;

  if (fp->proto == PROTO_LCP) {
    datalink_GotAuthname(dl, "");
    lcp->auth_ineed = lcp->want_auth;
    lcp->auth_iwait = lcp->his_auth;
    if (lcp->his_auth || lcp->want_auth) {
      if (bundle_Phase(dl->bundle) != PHASE_NETWORK)
        bundle_NewPhase(dl->bundle, PHASE_AUTHENTICATE);
      log_Printf(LogPHASE, "%s: his = %s, mine = %s\n", dl->name,
                Auth2Nam(lcp->his_auth, lcp->his_authtype),
                Auth2Nam(lcp->want_auth, lcp->want_authtype));
      if (lcp->his_auth == PROTO_PAP)
        auth_StartReq(&dl->pap);
      if (lcp->want_auth == PROTO_CHAP)
        auth_StartReq(&dl->chap.auth);
    } else
      datalink_AuthOk(dl);
  } else if (fp->proto == PROTO_CCP)
    (*dl->parent->LayerUp)(dl->parent->object, &dl->physical->link.ccp.fsm);
}