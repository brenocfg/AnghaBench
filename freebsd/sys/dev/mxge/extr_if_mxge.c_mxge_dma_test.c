#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  bus_addr; } ;
struct TYPE_8__ {int tx_boundary; int read_dma; int write_dma; int read_write_dma; int /*<<< orphan*/  dev; TYPE_1__ dmabench_dma; } ;
typedef  TYPE_2__ mxge_softc_t ;
struct TYPE_9__ {int data0; int data2; void* data1; } ;
typedef  TYPE_3__ mxge_cmd_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int MXGEFW_CMD_UNALIGNED_TEST ; 
 void* MXGE_HIGHPART_TO_U32 (int /*<<< orphan*/ ) ; 
 void* MXGE_LOWPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int mxge_send_cmd (TYPE_2__*,int,TYPE_3__*) ; 

__attribute__((used)) static int
mxge_dma_test(mxge_softc_t *sc, int test_type)
{
	mxge_cmd_t cmd;
	bus_addr_t dmatest_bus = sc->dmabench_dma.bus_addr;
	int status;
	uint32_t len;
	char *test = " ";


	/* Run a small DMA test.
	 * The magic multipliers to the length tell the firmware
	 * to do DMA read, write, or read+write tests.  The
	 * results are returned in cmd.data0.  The upper 16
	 * bits of the return is the number of transfers completed.
	 * The lower 16 bits is the time in 0.5us ticks that the
	 * transfers took to complete.
	 */

	len = sc->tx_boundary;

	cmd.data0 = MXGE_LOWPART_TO_U32(dmatest_bus);
	cmd.data1 = MXGE_HIGHPART_TO_U32(dmatest_bus);
	cmd.data2 = len * 0x10000;
	status = mxge_send_cmd(sc, test_type, &cmd);
	if (status != 0) {
		test = "read";
		goto abort;
	}
	sc->read_dma = ((cmd.data0>>16) * len * 2) /
		(cmd.data0 & 0xffff);
	cmd.data0 = MXGE_LOWPART_TO_U32(dmatest_bus);
	cmd.data1 = MXGE_HIGHPART_TO_U32(dmatest_bus);
	cmd.data2 = len * 0x1;
	status = mxge_send_cmd(sc, test_type, &cmd);
	if (status != 0) {
		test = "write";
		goto abort;
	}
	sc->write_dma = ((cmd.data0>>16) * len * 2) /
		(cmd.data0 & 0xffff);

	cmd.data0 = MXGE_LOWPART_TO_U32(dmatest_bus);
	cmd.data1 = MXGE_HIGHPART_TO_U32(dmatest_bus);
	cmd.data2 = len * 0x10001;
	status = mxge_send_cmd(sc, test_type, &cmd);
	if (status != 0) {
		test = "read/write";
		goto abort;
	}
	sc->read_write_dma = ((cmd.data0>>16) * len * 2 * 2) /
		(cmd.data0 & 0xffff);

abort:
	if (status != 0 && test_type != MXGEFW_CMD_UNALIGNED_TEST)
		device_printf(sc->dev, "DMA %s benchmark failed: %d\n",
			      test, status);

	return status;
}