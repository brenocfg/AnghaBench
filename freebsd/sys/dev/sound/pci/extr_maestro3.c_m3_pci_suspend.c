#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sc_info {int pch_cnt; int rch_cnt; int /*<<< orphan*/ * savemem; TYPE_1__* rch; TYPE_2__* pch; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ active; } ;
struct TYPE_3__ {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSP_CONTROL_C ; 
 int /*<<< orphan*/  CHANGE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HOST_INT_CTRL ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  PCMTRIG_STOP ; 
 int REV_B_CODE_MEMORY_BEGIN ; 
 int REV_B_CODE_MEMORY_END ; 
 int REV_B_DATA_MEMORY_BEGIN ; 
 int REV_B_DATA_MEMORY_END ; 
 int /*<<< orphan*/  m3_assp_halt (struct sc_info*) ; 
 int /*<<< orphan*/  m3_pchan_trigger_locked (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_power (struct sc_info*,int) ; 
 int /*<<< orphan*/  m3_rchan_trigger_locked (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_rd_assp_code (struct sc_info*,int) ; 
 int /*<<< orphan*/  m3_rd_assp_data (struct sc_info*,int) ; 
 int /*<<< orphan*/  m3_wr_1 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_wr_2 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m3_pci_suspend(device_t dev)
{
	struct sc_info *sc = pcm_getdevinfo(dev);
	int i, index = 0;

        M3_DEBUG(CHANGE, ("m3_pci_suspend\n"));

	M3_LOCK(sc);
	for (i=0 ; i<sc->pch_cnt ; i++) {
		if (sc->pch[i].active) {
			m3_pchan_trigger_locked(NULL, &sc->pch[i],
			    PCMTRIG_STOP);
		}
	}
	for (i=0 ; i<sc->rch_cnt ; i++) {
		if (sc->rch[i].active) {
			m3_rchan_trigger_locked(NULL, &sc->rch[i],
			    PCMTRIG_STOP);
		}
	}
	DELAY(10 * 1000); /* give things a chance to stop */

	/* Disable interrupts */
	m3_wr_2(sc, HOST_INT_CTRL, 0);
	m3_wr_1(sc, ASSP_CONTROL_C, 0);

	m3_assp_halt(sc);

	/* Save the state of the ASSP */
	for (i = REV_B_CODE_MEMORY_BEGIN; i <= REV_B_CODE_MEMORY_END; i++)
		sc->savemem[index++] = m3_rd_assp_code(sc, i);
	for (i = REV_B_DATA_MEMORY_BEGIN; i <= REV_B_DATA_MEMORY_END; i++)
		sc->savemem[index++] = m3_rd_assp_data(sc, i);

	/* Power down the card to D3 state */
	m3_power(sc, 3);
	M3_UNLOCK(sc);

	return 0;
}