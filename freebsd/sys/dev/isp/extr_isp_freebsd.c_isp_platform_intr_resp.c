#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIU2400_HCCR ; 
 int /*<<< orphan*/  HCCR_2400_CMD_CLEAR_RISC_INT ; 
 int /*<<< orphan*/  ISP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_intr_respq (int /*<<< orphan*/ *) ; 

void
isp_platform_intr_resp(void *arg)
{
	ispsoftc_t *isp = arg;

	ISP_LOCK(isp);
	isp_intr_respq(isp);
	ISP_UNLOCK(isp);

	/* We have handshake enabled, so explicitly complete interrupt */
	ISP_WRITE(isp, BIU2400_HCCR, HCCR_2400_CMD_CLEAR_RISC_INT);
}