#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_5__ {scalar_t__ ks_prefix; scalar_t__ ks_composed_char; scalar_t__ ks_accents; int /*<<< orphan*/  ks_state; scalar_t__ ks_polling; scalar_t__ ks_flags; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_MASK ; 

__attribute__((used)) static void
atkbd_clear_state(keyboard_t *kbd)
{
	atkbd_state_t *state;

	state = (atkbd_state_t *)kbd->kb_data;
	state->ks_flags = 0;
	state->ks_polling = 0;
	state->ks_state &= LOCK_MASK;	/* preserve locking key state */
	state->ks_accents = 0;
	state->ks_composed_char = 0;
#if 0
	state->ks_prefix = 0; /* XXX */
#endif
}