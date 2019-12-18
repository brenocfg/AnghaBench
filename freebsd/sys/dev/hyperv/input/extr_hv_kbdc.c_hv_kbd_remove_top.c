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
typedef  int /*<<< orphan*/  keystroke_info ;
struct TYPE_4__ {int /*<<< orphan*/  ks_mtx; int /*<<< orphan*/  ks_free_list; int /*<<< orphan*/  ks_queue; } ;
typedef  TYPE_1__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slink ; 

int
hv_kbd_remove_top(hv_kbd_sc *sc)
{
	int ret = 0;
	keystroke_info *ksi = NULL;
	mtx_lock(&sc->ks_mtx);
	if (STAILQ_EMPTY(&sc->ks_queue)) {
		DEBUG_HVSC(sc, "Empty queue!\n");
		ret = 1;
	} else {
		ksi = STAILQ_FIRST(&sc->ks_queue);
		STAILQ_REMOVE_HEAD(&sc->ks_queue, slink);
		LIST_INSERT_HEAD(&sc->ks_free_list, ksi, link);
	}
	mtx_unlock(&sc->ks_mtx);
	return (ret);
}