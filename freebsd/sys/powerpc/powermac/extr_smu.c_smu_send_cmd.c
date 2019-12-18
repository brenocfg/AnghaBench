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
struct smu_softc {int /*<<< orphan*/  sc_cmd_phys; int /*<<< orphan*/  sc_mailbox; int /*<<< orphan*/  sc_bt; int /*<<< orphan*/  sc_cmd_dmamap; int /*<<< orphan*/  sc_dmatag; TYPE_1__* sc_cmd; struct smu_cmd* sc_cur_cmd; scalar_t__ sc_u3; int /*<<< orphan*/  sc_mtx; } ;
struct smu_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  GPIO_DDR_OUTPUT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macgpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ powerpc_pow_enabled ; 
 int /*<<< orphan*/  smu_doorbell ; 

__attribute__((used)) static void
smu_send_cmd(device_t dev, struct smu_cmd *cmd)
{
	struct smu_softc *sc;

	sc = device_get_softc(dev);

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	if (sc->sc_u3)
		powerpc_pow_enabled = 0; /* SMU cannot work if we go to NAP */

	sc->sc_cur_cmd = cmd;

	/* Copy the command to the mailbox */
	sc->sc_cmd->cmd = cmd->cmd;
	sc->sc_cmd->len = cmd->len;
	memcpy(sc->sc_cmd->data, cmd->data, sizeof(cmd->data));
	bus_dmamap_sync(sc->sc_dmatag, sc->sc_cmd_dmamap, BUS_DMASYNC_PREWRITE);
	bus_space_write_4(sc->sc_bt, sc->sc_mailbox, 0, sc->sc_cmd_phys);

	/* Flush the cacheline it is in -- SMU bypasses the cache */
	__asm __volatile("sync; dcbf 0,%0; sync" :: "r"(sc->sc_cmd): "memory");

	/* Ring SMU doorbell */
	macgpio_write(smu_doorbell, GPIO_DDR_OUTPUT);
}