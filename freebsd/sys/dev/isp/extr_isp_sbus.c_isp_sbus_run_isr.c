#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {scalar_t__ isp_state; } ;
typedef  TYPE_1__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIU_ISR ; 
 int /*<<< orphan*/  BIU_SEMA ; 
 int BIU_SEMA_LOCK ; 
 int BXR2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCCR ; 
 int /*<<< orphan*/  HCCR_CMD_CLEAR_RISC_INT ; 
 int INT_PENDING_MASK (TYPE_1__*) ; 
 int /*<<< orphan*/  ISP_LOGDEBUG3 ; 
 scalar_t__ ISP_RUNSTATE ; 
 int /*<<< orphan*/  ISP_WRITE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IspVirt2Off (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MBOX_COMMAND_COMPLETE ; 
 int /*<<< orphan*/  OUTMAILBOX0 ; 
 int /*<<< orphan*/  isp_intr_async (TYPE_1__*,int) ; 
 int /*<<< orphan*/  isp_intr_mbox (TYPE_1__*,int) ; 
 int /*<<< orphan*/  isp_intr_respq (TYPE_1__*) ; 
 int /*<<< orphan*/  isp_prt (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void
isp_sbus_run_isr(ispsoftc_t *isp)
{
	uint16_t isr, sema, info;

	isr = BXR2(isp, IspVirt2Off(isp, BIU_ISR));
	sema = BXR2(isp, IspVirt2Off(isp, BIU_SEMA));
	isp_prt(isp, ISP_LOGDEBUG3, "ISR 0x%x SEMA 0x%x", isr, sema);
	isr &= INT_PENDING_MASK(isp);
	sema &= BIU_SEMA_LOCK;
	if (isr == 0 && sema == 0)
		return;
	if (sema != 0) {
		info = BXR2(isp, IspVirt2Off(isp, OUTMAILBOX0));
		if (info & MBOX_COMMAND_COMPLETE)
			isp_intr_mbox(isp, info);
		else
			isp_intr_async(isp, info);
		if (isp->isp_state == ISP_RUNSTATE)
			isp_intr_respq(isp);
	} else
		isp_intr_respq(isp);
	ISP_WRITE(isp, HCCR, HCCR_CMD_CLEAR_RISC_INT);
	if (sema)
		ISP_WRITE(isp, BIU_SEMA, 0);
}