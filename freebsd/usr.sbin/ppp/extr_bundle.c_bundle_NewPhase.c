#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {int /*<<< orphan*/  mp; } ;
struct bundle {size_t phase; TYPE_1__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  MPPE_MasterKeyValid ; 
#define  PHASE_AUTHENTICATE 132 
#define  PHASE_DEAD 131 
#define  PHASE_ESTABLISH 130 
#define  PHASE_NETWORK 129 
#define  PHASE_TERMINATE 128 
 int /*<<< orphan*/ * PhaseNames ; 
 int /*<<< orphan*/  bundle_Close (struct bundle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_DisplayPrompts () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mp_Down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_fsmStart (TYPE_1__*,struct bundle*) ; 

void
bundle_NewPhase(struct bundle *bundle, u_int new)
{
  if (new == bundle->phase)
    return;

  if (new <= PHASE_TERMINATE)
    log_Printf(LogPHASE, "bundle: %s\n", PhaseNames[new]);

  switch (new) {
  case PHASE_DEAD:
    bundle->phase = new;
#ifndef NODES
    MPPE_MasterKeyValid = 0;
#endif
    log_DisplayPrompts();
    break;

  case PHASE_ESTABLISH:
    bundle->phase = new;
    break;

  case PHASE_AUTHENTICATE:
    bundle->phase = new;
    log_DisplayPrompts();
    break;

  case PHASE_NETWORK:
    if (ncp_fsmStart(&bundle->ncp, bundle)) {
      bundle->phase = new;
      log_DisplayPrompts();
    } else {
      log_Printf(LogPHASE, "bundle: All NCPs are disabled\n");
      bundle_Close(bundle, NULL, CLOSE_STAYDOWN);
    }
    break;

  case PHASE_TERMINATE:
    bundle->phase = new;
    mp_Down(&bundle->ncp.mp);
    log_DisplayPrompts();
    break;
  }
}