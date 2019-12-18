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
struct TYPE_6__ {int state; } ;
struct cbcp {TYPE_3__ fsm; TYPE_2__* p; } ;
struct TYPE_5__ {TYPE_1__* dl; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCBCP ; 
 int /*<<< orphan*/  cbcpstate (int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbcp_NewPhase(struct cbcp *cbcp, int new)
{
  if (cbcp->fsm.state != new) {
    log_Printf(LogCBCP, "%s: State change %s --> %s\n", cbcp->p->dl->name,
               cbcpstate(cbcp->fsm.state), cbcpstate(new));
    cbcp->fsm.state = new;
  }
}