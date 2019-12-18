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
struct TYPE_2__ {int /*<<< orphan*/  first; } ;
struct roff_man {int /*<<< orphan*/  roff; int /*<<< orphan*/  next; int /*<<< orphan*/  lastnamed; int /*<<< orphan*/  lastsec; scalar_t__ flags; int /*<<< orphan*/ * last_es; TYPE_1__ meta; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROFF_NEXT_CHILD ; 
 int /*<<< orphan*/  SEC_NONE ; 
 int /*<<< orphan*/  roff_setreg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char) ; 

void
roff_state_reset(struct roff_man *man)
{
	man->last = man->meta.first;
	man->last_es = NULL;
	man->flags = 0;
	man->lastsec = man->lastnamed = SEC_NONE;
	man->next = ROFF_NEXT_CHILD;
	roff_setreg(man->roff, "nS", 0, '=');
}