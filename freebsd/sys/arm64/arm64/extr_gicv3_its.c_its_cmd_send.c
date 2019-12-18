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
typedef  scalar_t__ uint64_t ;
struct its_col {scalar_t__ col_target; } ;
struct TYPE_2__ {struct its_col* col; } ;
struct its_cmd_desc {TYPE_1__ cmd_desc_sync; int /*<<< orphan*/  cmd_type; } ;
struct its_cmd {int dummy; } ;
struct gicv3_its_softc {int sc_its_cmd_next_idx; int /*<<< orphan*/  sc_its_cmd_lock; struct its_cmd* sc_its_cmd_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GITS_CWRITER ; 
 int /*<<< orphan*/  ITS_CMD_SYNC ; 
 scalar_t__ ITS_TARGET_NONE ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gic_its_write_8 (struct gicv3_its_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct its_cmd* its_cmd_alloc_locked (int /*<<< orphan*/ ) ; 
 scalar_t__ its_cmd_prepare (struct its_cmd*,struct its_cmd_desc*) ; 
 int /*<<< orphan*/  its_cmd_sync (struct gicv3_its_softc*,struct its_cmd*) ; 
 int /*<<< orphan*/  its_cmd_wait_completion (int /*<<< orphan*/ ,struct its_cmd*,struct its_cmd*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
its_cmd_send(device_t dev, struct its_cmd_desc *desc)
{
	struct gicv3_its_softc *sc;
	struct its_cmd *cmd, *cmd_sync, *cmd_write;
	struct its_col col_sync;
	struct its_cmd_desc desc_sync;
	uint64_t target, cwriter;

	sc = device_get_softc(dev);
	mtx_lock_spin(&sc->sc_its_cmd_lock);
	cmd = its_cmd_alloc_locked(dev);
	if (cmd == NULL) {
		device_printf(dev, "could not allocate ITS command\n");
		mtx_unlock_spin(&sc->sc_its_cmd_lock);
		return (EBUSY);
	}

	target = its_cmd_prepare(cmd, desc);
	its_cmd_sync(sc, cmd);

	if (target != ITS_TARGET_NONE) {
		cmd_sync = its_cmd_alloc_locked(dev);
		if (cmd_sync != NULL) {
			desc_sync.cmd_type = ITS_CMD_SYNC;
			col_sync.col_target = target;
			desc_sync.cmd_desc_sync.col = &col_sync;
			its_cmd_prepare(cmd_sync, &desc_sync);
			its_cmd_sync(sc, cmd_sync);
		}
	}

	/* Update GITS_CWRITER */
	cwriter = sc->sc_its_cmd_next_idx * sizeof(struct its_cmd);
	gic_its_write_8(sc, GITS_CWRITER, cwriter);
	cmd_write = &sc->sc_its_cmd_base[sc->sc_its_cmd_next_idx];
	mtx_unlock_spin(&sc->sc_its_cmd_lock);

	its_cmd_wait_completion(dev, cmd, cmd_write);

	return (0);
}