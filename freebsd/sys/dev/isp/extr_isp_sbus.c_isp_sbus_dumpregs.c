#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  isp_dev; } ;
typedef  TYPE_1__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIU_CONF1 ; 
 int /*<<< orphan*/  BIU_ICR ; 
 int /*<<< orphan*/  BIU_ISR ; 
 int /*<<< orphan*/  BIU_SEMA ; 
 int /*<<< orphan*/  CDMA_CONF ; 
 int /*<<< orphan*/  CDMA_FIFO_STS ; 
 int /*<<< orphan*/  CDMA_STATUS ; 
 int /*<<< orphan*/  DDMA_CONF ; 
 int /*<<< orphan*/  DDMA_FIFO_STS ; 
 int /*<<< orphan*/  DDMA_STATUS ; 
 int /*<<< orphan*/  HCCR ; 
 int /*<<< orphan*/  HCCR_CMD_PAUSE ; 
 int /*<<< orphan*/  HCCR_CMD_RELEASE ; 
 int ISP_READ (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_WRITE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTMAILBOX0 ; 
 int /*<<< orphan*/  OUTMAILBOX1 ; 
 int /*<<< orphan*/  OUTMAILBOX2 ; 
 int /*<<< orphan*/  OUTMAILBOX3 ; 
 int /*<<< orphan*/  OUTMAILBOX4 ; 
 int /*<<< orphan*/  SXP_GROSS_ERR ; 
 int /*<<< orphan*/  SXP_INTERRUPT ; 
 int /*<<< orphan*/  SXP_PINS_CTRL ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
isp_sbus_dumpregs(ispsoftc_t *isp, const char *msg)
{
	if (msg)
		printf("%s: %s\n", device_get_nameunit(isp->isp_dev), msg);
	else
		printf("%s:\n", device_get_nameunit(isp->isp_dev));
	printf("    biu_conf1=%x", ISP_READ(isp, BIU_CONF1));
	printf(" biu_icr=%x biu_isr=%x biu_sema=%x ", ISP_READ(isp, BIU_ICR),
	    ISP_READ(isp, BIU_ISR), ISP_READ(isp, BIU_SEMA));
	printf("risc_hccr=%x\n", ISP_READ(isp, HCCR));


	ISP_WRITE(isp, HCCR, HCCR_CMD_PAUSE);
	printf("    cdma_conf=%x cdma_sts=%x cdma_fifostat=%x\n",
		ISP_READ(isp, CDMA_CONF), ISP_READ(isp, CDMA_STATUS),
		ISP_READ(isp, CDMA_FIFO_STS));
	printf("    ddma_conf=%x ddma_sts=%x ddma_fifostat=%x\n",
		ISP_READ(isp, DDMA_CONF), ISP_READ(isp, DDMA_STATUS),
		ISP_READ(isp, DDMA_FIFO_STS));
	printf("    sxp_int=%x sxp_gross=%x sxp(scsi_ctrl)=%x\n",
		ISP_READ(isp, SXP_INTERRUPT),
		ISP_READ(isp, SXP_GROSS_ERR),
		ISP_READ(isp, SXP_PINS_CTRL));
	ISP_WRITE(isp, HCCR, HCCR_CMD_RELEASE);
	printf("    mbox regs: %x %x %x %x %x\n",
	    ISP_READ(isp, OUTMAILBOX0), ISP_READ(isp, OUTMAILBOX1),
	    ISP_READ(isp, OUTMAILBOX2), ISP_READ(isp, OUTMAILBOX3),
	    ISP_READ(isp, OUTMAILBOX4));
}