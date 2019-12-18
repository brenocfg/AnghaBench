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
struct mbuf {int dummy; } ;
struct TYPE_6__ {TYPE_1__* link; } ;
struct TYPE_5__ {TYPE_3__ fsm; } ;
struct link {TYPE_2__ ccp; } ;
struct bundle {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 int /*<<< orphan*/  MB_CCPIN ; 
 scalar_t__ PHASE_NETWORK ; 
 scalar_t__ bundle_Phase (struct bundle*) ; 
 int /*<<< orphan*/  bundle_PhaseName (struct bundle*) ; 
 int /*<<< orphan*/  fsm_Input (TYPE_3__*,struct mbuf*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_settype (struct mbuf*,int /*<<< orphan*/ ) ; 

extern struct mbuf *
ccp_Input(struct bundle *bundle, struct link *l, struct mbuf *bp)
{
  /* Got PROTO_CCP from link */
  m_settype(bp, MB_CCPIN);
  if (bundle_Phase(bundle) == PHASE_NETWORK)
    fsm_Input(&l->ccp.fsm, bp);
  else {
    if (bundle_Phase(bundle) < PHASE_NETWORK)
      log_Printf(LogCCP, "%s: Error: Unexpected CCP in phase %s (ignored)\n",
                 l->ccp.fsm.link->name, bundle_PhaseName(bundle));
    m_freem(bp);
  }
  return NULL;
}