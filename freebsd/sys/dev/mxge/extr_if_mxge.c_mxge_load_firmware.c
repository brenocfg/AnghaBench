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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  map; int /*<<< orphan*/  dmat; int /*<<< orphan*/  bus_addr; } ;
struct TYPE_7__ {int sram_size; int tx_boundary; int /*<<< orphan*/  dev; TYPE_1__ cmd_dma; scalar_t__ sram; scalar_t__ cmd; int /*<<< orphan*/  fw_name; } ;
typedef  TYPE_2__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 scalar_t__ MXGEFW_BOOT_HANDOFF ; 
 int MXGE_FW_OFFSET ; 
 int MXGE_HIGHPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int MXGE_LOWPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int htobe32 (int) ; 
 int mxge_adopt_running_firmware (TYPE_2__*) ; 
 int /*<<< orphan*/  mxge_fw_unaligned ; 
 int mxge_load_firmware_helper (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  mxge_pio_copy (char volatile*,int*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
mxge_load_firmware(mxge_softc_t *sc, int adopt)
{
	volatile uint32_t *confirm;
	volatile char *submit;
	char buf_bytes[72];
	uint32_t *buf, size, dma_low, dma_high;
	int status, i;

	buf = (uint32_t *)((unsigned long)(buf_bytes + 7) & ~7UL);

	size = sc->sram_size;
	status = mxge_load_firmware_helper(sc, &size);
	if (status) {
		if (!adopt)
			return status;
		/* Try to use the currently running firmware, if
		   it is new enough */
		status = mxge_adopt_running_firmware(sc);
		if (status) {
			device_printf(sc->dev,
				      "failed to adopt running firmware\n");
			return status;
		}
		device_printf(sc->dev,
			      "Successfully adopted running firmware\n");
		if (sc->tx_boundary == 4096) {
			device_printf(sc->dev,
				"Using firmware currently running on NIC"
				 ".  For optimal\n");
			device_printf(sc->dev,
				 "performance consider loading optimized "
				 "firmware\n");
		}
		sc->fw_name = mxge_fw_unaligned;
		sc->tx_boundary = 2048;
		return 0;
	}
	/* clear confirmation addr */
	confirm = (volatile uint32_t *)sc->cmd;
	*confirm = 0;
	wmb();
	/* send a reload command to the bootstrap MCP, and wait for the
	   response in the confirmation address.  The firmware should
	   write a -1 there to indicate it is alive and well
	*/

	dma_low = MXGE_LOWPART_TO_U32(sc->cmd_dma.bus_addr);
	dma_high = MXGE_HIGHPART_TO_U32(sc->cmd_dma.bus_addr);

	buf[0] = htobe32(dma_high);	/* confirm addr MSW */
	buf[1] = htobe32(dma_low);	/* confirm addr LSW */
	buf[2] = htobe32(0xffffffff);	/* confirm data */

	/* FIX: All newest firmware should un-protect the bottom of
	   the sram before handoff. However, the very first interfaces
	   do not. Therefore the handoff copy must skip the first 8 bytes
	*/
					/* where the code starts*/
	buf[3] = htobe32(MXGE_FW_OFFSET + 8);
	buf[4] = htobe32(size - 8); 	/* length of code */
	buf[5] = htobe32(8);		/* where to copy to */
	buf[6] = htobe32(0);		/* where to jump to */

	submit = (volatile char *)(sc->sram + MXGEFW_BOOT_HANDOFF);
	mxge_pio_copy(submit, buf, 64);
	wmb();
	DELAY(1000);
	wmb();
	i = 0;
	while (*confirm != 0xffffffff && i < 20) {
		DELAY(1000*10);
		i++;
		bus_dmamap_sync(sc->cmd_dma.dmat,
				sc->cmd_dma.map, BUS_DMASYNC_POSTREAD);
	}
	if (*confirm != 0xffffffff) {
		device_printf(sc->dev,"handoff failed (%p = 0x%x)",
			confirm, *confirm);
		
		return ENXIO;
	}
	return 0;
}