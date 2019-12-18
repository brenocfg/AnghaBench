#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct edge {int /*<<< orphan*/  edom; TYPE_3__* succ; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  edgewords; } ;
typedef  TYPE_4__ opt_state_t ;
struct TYPE_7__ {int /*<<< orphan*/  edom; } ;
struct TYPE_6__ {int /*<<< orphan*/  edom; } ;
struct TYPE_8__ {TYPE_2__ ef; TYPE_1__ et; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_INTERSECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
propedom(opt_state_t *opt_state, struct edge *ep)
{
	SET_INSERT(ep->edom, ep->id);
	if (ep->succ) {
		SET_INTERSECT(ep->succ->et.edom, ep->edom, opt_state->edgewords);
		SET_INTERSECT(ep->succ->ef.edom, ep->edom, opt_state->edgewords);
	}
}