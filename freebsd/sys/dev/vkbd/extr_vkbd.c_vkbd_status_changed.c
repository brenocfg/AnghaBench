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
struct TYPE_4__ {int ks_flags; int /*<<< orphan*/  ks_rsel; } ;
typedef  TYPE_1__ vkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PZERO ; 
 int STATUS ; 
 int /*<<< orphan*/  VKBD_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
vkbd_status_changed(vkbd_state_t *state)
{
	VKBD_LOCK_ASSERT(state, MA_OWNED);

	if (!(state->ks_flags & STATUS)) {
		state->ks_flags |= STATUS;
		selwakeuppri(&state->ks_rsel, PZERO + 1);
		wakeup(&state->ks_flags);
	}
}