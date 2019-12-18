#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct link {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_4__ {TYPE_1__ ipv6cp; } ;
struct bundle {TYPE_2__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogIPV6CP ; 
 int /*<<< orphan*/  MB_IPV6CPIN ; 
 scalar_t__ PHASE_NETWORK ; 
 scalar_t__ bundle_Phase (struct bundle*) ; 
 int /*<<< orphan*/  bundle_PhaseName (struct bundle*) ; 
 int /*<<< orphan*/  fsm_Input (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_settype (struct mbuf*,int /*<<< orphan*/ ) ; 

struct mbuf *
ipv6cp_Input(struct bundle *bundle, struct link *l, struct mbuf *bp)
{
  /* Got PROTO_IPV6CP from link */
  m_settype(bp, MB_IPV6CPIN);
  if (bundle_Phase(bundle) == PHASE_NETWORK)
    fsm_Input(&bundle->ncp.ipv6cp.fsm, bp);
  else {
    if (bundle_Phase(bundle) < PHASE_NETWORK)
      log_Printf(LogIPV6CP, "%s: Error: Unexpected IPV6CP in phase %s"
                 " (ignored)\n", l->name, bundle_PhaseName(bundle));
    m_freem(bp);
  }
  return NULL;
}