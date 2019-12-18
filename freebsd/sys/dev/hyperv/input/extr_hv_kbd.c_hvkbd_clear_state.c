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
struct TYPE_4__ {TYPE_2__* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_5__ {int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_state; } ;
typedef  TYPE_2__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  HVKBD_FLAG_POLLING ; 
 int /*<<< orphan*/  LOCK_MASK ; 

__attribute__((used)) static void
hvkbd_clear_state(keyboard_t *kbd)
{
	hv_kbd_sc *sc = kbd->kb_data;
	sc->sc_state &= LOCK_MASK;	/* preserve locking key state */
	sc->sc_flags &= ~HVKBD_FLAG_POLLING;
}