#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ks; } ;
typedef  TYPE_1__ keystroke_info ;
typedef  int /*<<< orphan*/  keystroke ;
struct TYPE_9__ {int /*<<< orphan*/  ks_mtx; int /*<<< orphan*/  ks_queue; int /*<<< orphan*/  ks_free_list; } ;
typedef  TYPE_2__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_2__*,char*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slink ; 

int
hv_kbd_produce_ks(hv_kbd_sc *sc, const keystroke *ks)
{
	int ret = 0;
	keystroke_info *ksi;
	mtx_lock(&sc->ks_mtx);
	if (LIST_EMPTY(&sc->ks_free_list)) {
		DEBUG_HVSC(sc, "NO buffer!\n");
		ret = 1;
	} else {
		ksi = LIST_FIRST(&sc->ks_free_list);
		LIST_REMOVE(ksi, link);
		ksi->ks = *ks;
		STAILQ_INSERT_TAIL(&sc->ks_queue, ksi, slink);
	}
	mtx_unlock(&sc->ks_mtx);
	return (ret);
}