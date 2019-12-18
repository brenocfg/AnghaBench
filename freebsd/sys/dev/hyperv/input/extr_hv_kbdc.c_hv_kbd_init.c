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
struct TYPE_3__ {int /*<<< orphan*/  ks_free_list; int /*<<< orphan*/  ks_queue; int /*<<< orphan*/  ks_mtx; } ;
typedef  TYPE_1__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hv_kbd_init(hv_kbd_sc *sc)
{
	const int max_list = 16;
	int i;
	keystroke_info *ksi;

	mtx_init(&sc->ks_mtx, "hv_kbdc mutex", NULL, MTX_DEF);
	LIST_INIT(&sc->ks_free_list);
	STAILQ_INIT(&sc->ks_queue);
	for (i = 0; i < max_list; i++) {
		ksi = malloc(sizeof(keystroke_info),
		    M_DEVBUF, M_WAITOK|M_ZERO);
		LIST_INSERT_HEAD(&sc->ks_free_list, ksi, link);
	}
}