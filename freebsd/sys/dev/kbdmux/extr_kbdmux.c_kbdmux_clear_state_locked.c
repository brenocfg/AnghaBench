#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ks_inq_length; scalar_t__ ks_composed_char; scalar_t__ ks_accents; int /*<<< orphan*/  ks_state; scalar_t__ ks_polling; int /*<<< orphan*/  ks_flags; } ;
typedef  TYPE_1__ kbdmux_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPOSE ; 
 int /*<<< orphan*/  KBDMUX_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static void
kbdmux_clear_state_locked(kbdmux_state_t *state)
{
	KBDMUX_LOCK_ASSERT(state, MA_OWNED);

	state->ks_flags &= ~COMPOSE;
	state->ks_polling = 0;
	state->ks_state &= LOCK_MASK;	/* preserve locking key state */
	state->ks_accents = 0;
	state->ks_composed_char = 0;
/*	state->ks_prefix = 0;		XXX */
	state->ks_inq_length = 0;
}