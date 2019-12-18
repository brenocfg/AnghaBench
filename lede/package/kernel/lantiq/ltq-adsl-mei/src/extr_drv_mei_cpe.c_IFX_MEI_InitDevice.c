#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  smmu_mem_info_t ;
typedef  int /*<<< orphan*/  ifx_mei_device_private_t ;
struct TYPE_7__ {int /*<<< orphan*/  mei_cmv_sema; int /*<<< orphan*/  wait_queue_modemready; int /*<<< orphan*/  wait_queue_arcmsgav; scalar_t__ arcmsgav; scalar_t__ modem_ready; int /*<<< orphan*/ * adsl_mem_info; } ;
struct TYPE_6__ {int /*<<< orphan*/ * nIrq; scalar_t__ nInUse; scalar_t__ base_address; int /*<<< orphan*/ * pPriv; } ;
typedef  TYPE_1__ DSL_DEV_Device_t ;

/* Variables and functions */
 TYPE_4__* DSL_DEV_PRIVATE (TYPE_1__*) ; 
 int ENOMEM ; 
 size_t IFX_DFEIR ; 
 size_t IFX_DYING_GASP ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_IrqHandle ; 
 scalar_t__ KSEG1 ; 
 scalar_t__ LTQ_MEI_BASE_ADDR ; 
 int /*<<< orphan*/  LTQ_MEI_DYING_GASP_INT ; 
 int /*<<< orphan*/  LTQ_MEI_INT ; 
 int* LTQ_PMU_PWDCR ; 
 int MAX_BAR_REGISTERS ; 
 int /*<<< orphan*/  MEI_INIT_WAKELIST (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEI_MASK_AND_ACK_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEI_MUTEX_INIT (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* dsl_devices ; 
 int ltq_r32 (int*) ; 
 int /*<<< orphan*/  ltq_w32 (int,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * sDanube_Mei_Private ; 

__attribute__((used)) static int
IFX_MEI_InitDevice (int num)
{
	DSL_DEV_Device_t *pDev;
        u32 temp;
	pDev = &dsl_devices[num];
	if (pDev == NULL)
		return -ENOMEM;
	pDev->pPriv = &sDanube_Mei_Private[num];
	memset (pDev->pPriv, 0, sizeof (ifx_mei_device_private_t));

	memset (&DSL_DEV_PRIVATE(pDev)->
		adsl_mem_info[0], 0,
		sizeof (smmu_mem_info_t) * MAX_BAR_REGISTERS);

	if (num == 0) {
		pDev->nIrq[IFX_DFEIR]      = LTQ_MEI_INT;
		pDev->nIrq[IFX_DYING_GASP] = LTQ_MEI_DYING_GASP_INT;
		pDev->base_address = KSEG1 + LTQ_MEI_BASE_ADDR;

                /* Power up MEI */
#ifdef CONFIG_LANTIQ_AMAZON_SE
		*LTQ_PMU_PWDCR &= ~(1 << 9);  // enable dsl
		*LTQ_PMU_PWDCR &= ~(1 << 15); // enable AHB base
#endif
		temp = ltq_r32(LTQ_PMU_PWDCR);
		temp &= 0xffff7dbe;
		ltq_w32(temp, LTQ_PMU_PWDCR);
	}
	pDev->nInUse = 0;
	DSL_DEV_PRIVATE(pDev)->modem_ready = 0;
	DSL_DEV_PRIVATE(pDev)->arcmsgav = 0;

	MEI_INIT_WAKELIST ("arcq", DSL_DEV_PRIVATE(pDev)->wait_queue_arcmsgav);	// for ARCMSGAV
	MEI_INIT_WAKELIST ("arcr", DSL_DEV_PRIVATE(pDev)->wait_queue_modemready);	// for arc modem ready

	MEI_MUTEX_INIT (DSL_DEV_PRIVATE(pDev)->mei_cmv_sema, 1);	// semaphore initialization, mutex
#if 0
	MEI_MASK_AND_ACK_IRQ (pDev->nIrq[IFX_DFEIR]);
	MEI_MASK_AND_ACK_IRQ (pDev->nIrq[IFX_DYING_GASP]);
#endif
	if (request_irq (pDev->nIrq[IFX_DFEIR], IFX_MEI_IrqHandle, 0, "DFEIR", pDev) != 0) {
		IFX_MEI_EMSG ("request_irq %d failed!\n", pDev->nIrq[IFX_DFEIR]);
		return -1;
	}
	/*if (request_irq (pDev->nIrq[IFX_DYING_GASP], IFX_MEI_Dying_Gasp_IrqHandle, 0, "DYING_GASP", pDev) != 0) {
		IFX_MEI_EMSG ("request_irq %d failed!\n", pDev->nIrq[IFX_DYING_GASP]);
		return -1;
	}*/
//	IFX_MEI_DMSG("Device %d initialized. IER %#x\n", num, bsp_get_irq_ier(pDev->nIrq[IFX_DYING_GASP]));
	return 0;
}