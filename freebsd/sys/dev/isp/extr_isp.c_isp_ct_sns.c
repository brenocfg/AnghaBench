#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int* param; } ;
typedef  TYPE_1__ mbreg_t ;
struct TYPE_13__ {int isp_dblev; } ;
typedef  TYPE_2__ ispsoftc_t ;
struct TYPE_14__ {int /*<<< orphan*/  isp_scratch; int /*<<< orphan*/  isp_scdma; } ;
typedef  TYPE_3__ fcparam ;

/* Variables and functions */
 int DMA_WD0 (int /*<<< orphan*/ ) ; 
 int DMA_WD1 (int /*<<< orphan*/ ) ; 
 int DMA_WD2 (int /*<<< orphan*/ ) ; 
 int DMA_WD3 (int /*<<< orphan*/ ) ; 
 TYPE_3__* FCPARAM (TYPE_2__*,int) ; 
 int ISP_LOGDEBUG1 ; 
 int /*<<< orphan*/  MBLOGALL ; 
 int MBOX_COMMAND_COMPLETE ; 
 int MBOX_INVALID_COMMAND ; 
 int /*<<< orphan*/  MBOX_SEND_SNS ; 
 int /*<<< orphan*/  MBSINIT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEMORYBARRIER (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SYNC_SFORCPU ; 
 int /*<<< orphan*/  SYNC_SFORDEV ; 
 int /*<<< orphan*/  isp_mboxcmd (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_print_bytes (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isp_ct_sns(ispsoftc_t *isp, int chan, uint32_t cmd_bcnt, uint32_t rsp_bcnt)
{
	fcparam *fcp = FCPARAM(isp, chan);
	mbreg_t mbs;

	if (isp->isp_dblev & ISP_LOGDEBUG1)
		isp_print_bytes(isp, "CT SNS request", cmd_bcnt, fcp->isp_scratch);
	MEMORYBARRIER(isp, SYNC_SFORDEV, 0, cmd_bcnt, chan);

	MBSINIT(&mbs, MBOX_SEND_SNS, MBLOGALL, 10000000);
	mbs.param[1] = cmd_bcnt >> 1;
	mbs.param[2] = DMA_WD1(fcp->isp_scdma);
	mbs.param[3] = DMA_WD0(fcp->isp_scdma);
	mbs.param[6] = DMA_WD3(fcp->isp_scdma);
	mbs.param[7] = DMA_WD2(fcp->isp_scdma);
	isp_mboxcmd(isp, &mbs);
	if (mbs.param[0] != MBOX_COMMAND_COMPLETE) {
		if (mbs.param[0] == MBOX_INVALID_COMMAND) {
			return (1);
		} else {
			return (-1);
		}
	}

	MEMORYBARRIER(isp, SYNC_SFORCPU, 0, rsp_bcnt, chan);
	if (isp->isp_dblev & ISP_LOGDEBUG1)
		isp_print_bytes(isp, "CT response", rsp_bcnt, fcp->isp_scratch);
	return (0);
}