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
struct mcp_slot {int dummy; } ;
struct TYPE_8__ {int num_slices; char* fw_name; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ mxge_softc_t ;
struct TYPE_9__ {int data0; } ;
typedef  TYPE_2__ mxge_cmd_t ;
typedef  int /*<<< orphan*/  mcp_dma_addr_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MXGEFW_CMD_GET_MAX_RSS_QUEUES ; 
 int /*<<< orphan*/  MXGEFW_CMD_GET_RX_RING_SIZE ; 
 int /*<<< orphan*/  MXGEFW_CMD_RESET ; 
 int /*<<< orphan*/  MXGEFW_CMD_SET_INTRQ_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 char* mxge_fw_aligned ; 
 char* mxge_fw_rss_aligned ; 
 char* mxge_fw_rss_unaligned ; 
 int mxge_load_firmware (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mxge_max_slices ; 
 int mxge_send_cmd (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ mxge_verbose ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mxge_slice_probe(mxge_softc_t *sc)
{
	mxge_cmd_t cmd;
	char *old_fw;
	int msix_cnt, status, max_intr_slots;

	sc->num_slices = 1;
	/*
	 *  don't enable multiple slices if they are not enabled,
	 *  or if this is not an SMP system
	 */
	
	if (mxge_max_slices == 0 || mxge_max_slices == 1 || mp_ncpus < 2)
		return;

	/* see how many MSI-X interrupts are available */
	msix_cnt = pci_msix_count(sc->dev);
	if (msix_cnt < 2)
		return;

	/* now load the slice aware firmware see what it supports */
	old_fw = sc->fw_name;
	if (old_fw == mxge_fw_aligned)
		sc->fw_name = mxge_fw_rss_aligned;
	else
		sc->fw_name = mxge_fw_rss_unaligned;
	status = mxge_load_firmware(sc, 0);
	if (status != 0) {
		device_printf(sc->dev, "Falling back to a single slice\n");
		return;
	}
	
	/* try to send a reset command to the card to see if it
	   is alive */
	memset(&cmd, 0, sizeof (cmd));
	status = mxge_send_cmd(sc, MXGEFW_CMD_RESET, &cmd);
	if (status != 0) {
		device_printf(sc->dev, "failed reset\n");
		goto abort_with_fw;
	}

	/* get rx ring size */
	status = mxge_send_cmd(sc, MXGEFW_CMD_GET_RX_RING_SIZE, &cmd);
	if (status != 0) {
		device_printf(sc->dev, "Cannot determine rx ring size\n");
		goto abort_with_fw;
	}
	max_intr_slots = 2 * (cmd.data0 / sizeof (mcp_dma_addr_t));

	/* tell it the size of the interrupt queues */
	cmd.data0 = max_intr_slots * sizeof (struct mcp_slot);
	status = mxge_send_cmd(sc, MXGEFW_CMD_SET_INTRQ_SIZE, &cmd);
	if (status != 0) {
		device_printf(sc->dev, "failed MXGEFW_CMD_SET_INTRQ_SIZE\n");
		goto abort_with_fw;
	}

	/* ask the maximum number of slices it supports */
	status = mxge_send_cmd(sc, MXGEFW_CMD_GET_MAX_RSS_QUEUES, &cmd);
	if (status != 0) {
		device_printf(sc->dev,
			      "failed MXGEFW_CMD_GET_MAX_RSS_QUEUES\n");
		goto abort_with_fw;
	}
	sc->num_slices = cmd.data0;
	if (sc->num_slices > msix_cnt)
		sc->num_slices = msix_cnt;

	if (mxge_max_slices == -1) {
		/* cap to number of CPUs in system */
		if (sc->num_slices > mp_ncpus)
			sc->num_slices = mp_ncpus;
	} else {
		if (sc->num_slices > mxge_max_slices)
			sc->num_slices = mxge_max_slices;
	}
	/* make sure it is a power of two */
	while (sc->num_slices & (sc->num_slices - 1))
		sc->num_slices--;

	if (mxge_verbose)
		device_printf(sc->dev, "using %d slices\n",
			      sc->num_slices);
	
	return;

abort_with_fw:
	sc->fw_name = old_fw;
	(void) mxge_load_firmware(sc, 0);
}