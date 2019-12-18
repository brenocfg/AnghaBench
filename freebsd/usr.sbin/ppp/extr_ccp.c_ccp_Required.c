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
struct ccp {int /*<<< orphan*/  fsm; TYPE_1__ cfg; } ;
struct TYPE_4__ {size_t Neg; scalar_t__ (* Required ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 unsigned int NALGORITHMS ; 
 TYPE_2__** algorithm ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

int
ccp_Required(struct ccp *ccp)
{
  unsigned f;

  for (f = 0; f < NALGORITHMS; f++)
    if (IsEnabled(ccp->cfg.neg[algorithm[f]->Neg]) &&
        (*algorithm[f]->Required)(&ccp->fsm))
      return 1;

  return 0;
}