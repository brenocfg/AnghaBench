#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cc; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_5__ {TYPE_2__ ks_inq; int /*<<< orphan*/  ks_wsel; scalar_t__ ks_composed_char; scalar_t__ ks_accents; int /*<<< orphan*/  ks_state; scalar_t__ ks_polling; int /*<<< orphan*/  ks_flags; } ;
typedef  TYPE_1__ vkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPOSE ; 
 int /*<<< orphan*/  LOCK_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  VKBD_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (TYPE_2__*) ; 

__attribute__((used)) static void
vkbd_clear_state_locked(vkbd_state_t *state)
{
	VKBD_LOCK_ASSERT(state, MA_OWNED);

	state->ks_flags &= ~COMPOSE;
	state->ks_polling = 0;
	state->ks_state &= LOCK_MASK;	/* preserve locking key state */
	state->ks_accents = 0;
	state->ks_composed_char = 0;
/*	state->ks_prefix = 0;		XXX */

	/* flush ks_inq and wakeup writers/poll()ers */
	state->ks_inq.head = state->ks_inq.tail = state->ks_inq.cc = 0;
	selwakeuppri(&state->ks_wsel, PZERO + 1);
	wakeup(&state->ks_inq);
}