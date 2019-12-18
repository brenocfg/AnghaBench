#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ks; } ;
typedef  TYPE_1__ keystroke_info ;
typedef  int /*<<< orphan*/  keystroke ;
struct TYPE_7__ {int /*<<< orphan*/  ks_mtx; int /*<<< orphan*/  ks_queue; } ;
typedef  TYPE_2__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_2__*,char*) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
hv_kbd_modify_top(hv_kbd_sc *sc, keystroke *top)
{
	int ret = 0;
	keystroke_info *ksi = NULL;
	mtx_lock(&sc->ks_mtx);
	if (STAILQ_EMPTY(&sc->ks_queue)) {
		DEBUG_HVSC(sc, "Empty queue!\n");
		ret = 1;
	} else {
		ksi = STAILQ_FIRST(&sc->ks_queue);
		ksi->ks = *top;
	}
	mtx_unlock(&sc->ks_mtx);
	return (ret);
}