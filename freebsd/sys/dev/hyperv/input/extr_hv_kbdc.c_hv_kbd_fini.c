#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  keystroke_info ;
struct TYPE_3__ {int /*<<< orphan*/  ks_mtx; int /*<<< orphan*/  ks_queue; int /*<<< orphan*/  ks_free_list; } ;
typedef  TYPE_1__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slink ; 

__attribute__((used)) static void
hv_kbd_fini(hv_kbd_sc *sc)
{
	keystroke_info *ksi;
	while (!LIST_EMPTY(&sc->ks_free_list)) {
		ksi = LIST_FIRST(&sc->ks_free_list);
		LIST_REMOVE(ksi, link);
		free(ksi, M_DEVBUF);
	}
	while (!STAILQ_EMPTY(&sc->ks_queue)) {
		ksi = STAILQ_FIRST(&sc->ks_queue);
		STAILQ_REMOVE_HEAD(&sc->ks_queue, slink);
		free(ksi, M_DEVBUF);
	}
	mtx_destroy(&sc->ks_mtx);
}