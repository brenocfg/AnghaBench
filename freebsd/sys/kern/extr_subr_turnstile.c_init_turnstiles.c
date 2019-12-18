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
struct TYPE_4__ {int /*<<< orphan*/ * td_turnstile; int /*<<< orphan*/  td_contested; } ;
struct TYPE_3__ {int /*<<< orphan*/  tc_lock; int /*<<< orphan*/  tc_turnstiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int TC_TABLESIZE ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td_contested_lock ; 
 TYPE_2__ thread0 ; 
 TYPE_1__* turnstile_chains ; 

void
init_turnstiles(void)
{
	int i;

	for (i = 0; i < TC_TABLESIZE; i++) {
		LIST_INIT(&turnstile_chains[i].tc_turnstiles);
		mtx_init(&turnstile_chains[i].tc_lock, "turnstile chain",
		    NULL, MTX_SPIN);
	}
	mtx_init(&td_contested_lock, "td_contested", NULL, MTX_SPIN);
	LIST_INIT(&thread0.td_contested);
	thread0.td_turnstile = NULL;
}