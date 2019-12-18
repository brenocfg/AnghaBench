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
struct TYPE_3__ {int /*<<< orphan*/ * neg; } ;
struct TYPE_4__ {scalar_t__ open_mode; } ;
struct ccp {TYPE_1__ cfg; TYPE_2__ fsm; } ;

/* Variables and functions */
 int CCP_NEG_TOTAL ; 
 scalar_t__ IsAccepted (int /*<<< orphan*/ ) ; 
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 scalar_t__ OPEN_PASSIVE ; 

int
ccp_SetOpenMode(struct ccp *ccp)
{
  int f;

  for (f = 0; f < CCP_NEG_TOTAL; f++)
    if (IsEnabled(ccp->cfg.neg[f])) {
      ccp->fsm.open_mode = 0;
      return 1;
    }

  ccp->fsm.open_mode = OPEN_PASSIVE;	/* Go straight to ST_STOPPED ? */

  for (f = 0; f < CCP_NEG_TOTAL; f++)
    if (IsAccepted(ccp->cfg.neg[f]))
      return 1;

  return 0;				/* No CCP at all */
}