#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct emu_sc_info {int dbg_level; TYPE_1__* rm; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int last_free_gpr; scalar_t__* allocmap; int /*<<< orphan*/  gpr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
emu_rm_uninit(struct emu_sc_info *sc)
{
	int i;

	if (sc->dbg_level > 1) {
		mtx_lock(&(sc->rm->gpr_lock));
		for (i = 1; i < sc->rm->last_free_gpr; i++)
			if (sc->rm->allocmap[i] > 0)
				device_printf(sc->dev, "rm: gpr %d not free before uninit\n", i);
		mtx_unlock(&(sc->rm->gpr_lock));
	}

	mtx_destroy(&(sc->rm->gpr_lock));
	free(sc->rm, M_DEVBUF);
	return (0);
}