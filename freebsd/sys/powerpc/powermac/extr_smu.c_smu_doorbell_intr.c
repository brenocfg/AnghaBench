#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct smu_softc {int /*<<< orphan*/  sc_mtx; TYPE_2__* sc_cur_cmd; int /*<<< orphan*/  sc_cmdq; scalar_t__ sc_u3; TYPE_1__* sc_cmd; int /*<<< orphan*/  sc_cmd_dmamap; int /*<<< orphan*/  sc_dmatag; } ;
typedef  void* device_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int GPIO_DATA ; 
 int GPIO_DDR_OUTPUT ; 
 int GPIO_LEVEL_RO ; 
 TYPE_2__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_q ; 
 struct smu_softc* device_get_softc (void*) ; 
 int macgpio_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int powerpc_pow_enabled ; 
 int /*<<< orphan*/  smu_doorbell ; 
 int /*<<< orphan*/  smu_send_cmd (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_2__*) ; 

__attribute__((used)) static void
smu_doorbell_intr(void *xdev)
{
	device_t smu;
	struct smu_softc *sc;
	int doorbell_ack;

	smu = xdev;
	doorbell_ack = macgpio_read(smu_doorbell);
	sc = device_get_softc(smu);

	if (doorbell_ack != (GPIO_DDR_OUTPUT | GPIO_LEVEL_RO | GPIO_DATA)) 
		return;

	mtx_lock(&sc->sc_mtx);

	if (sc->sc_cur_cmd == NULL)	/* spurious */
		goto done;

	/* Check result. First invalidate the cache again... */
	__asm __volatile("dcbf 0,%0; sync" :: "r"(sc->sc_cmd) : "memory");
	
	bus_dmamap_sync(sc->sc_dmatag, sc->sc_cmd_dmamap, BUS_DMASYNC_POSTREAD);

	sc->sc_cur_cmd->cmd = sc->sc_cmd->cmd;
	sc->sc_cur_cmd->len = sc->sc_cmd->len;
	memcpy(sc->sc_cur_cmd->data, sc->sc_cmd->data,
	    sizeof(sc->sc_cmd->data));
	wakeup(sc->sc_cur_cmd);
	sc->sc_cur_cmd = NULL;
	if (sc->sc_u3)
		powerpc_pow_enabled = 1;

    done:
	/* Queue next command if one is pending */
	if (STAILQ_FIRST(&sc->sc_cmdq) != NULL) {
		sc->sc_cur_cmd = STAILQ_FIRST(&sc->sc_cmdq);
		STAILQ_REMOVE_HEAD(&sc->sc_cmdq, cmd_q);
		smu_send_cmd(smu, sc->sc_cur_cmd);
	}

	mtx_unlock(&sc->sc_mtx);
}