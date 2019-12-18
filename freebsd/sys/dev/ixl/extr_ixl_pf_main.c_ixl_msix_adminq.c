#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {TYPE_1__ vsi; int /*<<< orphan*/  state; int /*<<< orphan*/  admin_irq; int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTF (int /*<<< orphan*/ ,char*) ; 
 int FALSE ; 
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int /*<<< orphan*/  I40E_GLGEN_RSTAT ; 
 int I40E_GLGEN_RSTAT_RESET_TYPE_MASK ; 
 int I40E_GLGEN_RSTAT_RESET_TYPE_SHIFT ; 
 int /*<<< orphan*/  I40E_PFHMC_ERRORDATA ; 
 int /*<<< orphan*/  I40E_PFHMC_ERRORINFO ; 
 int I40E_PFHMC_ERRORINFO_ERROR_DETECTED_MASK ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0 ; 
 int I40E_PFINT_ICR0_ADMINQ_MASK ; 
 int I40E_PFINT_ICR0_ECC_ERR_MASK ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int I40E_PFINT_ICR0_ENA_ADMINQ_MASK ; 
 int I40E_PFINT_ICR0_ENA_GRST_MASK ; 
 int I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK ; 
 int I40E_PFINT_ICR0_ENA_VFLR_MASK ; 
 int I40E_PFINT_ICR0_GRST_MASK ; 
 int I40E_PFINT_ICR0_HMC_ERR_MASK ; 
 int I40E_PFINT_ICR0_MAL_DETECT_MASK ; 
 int I40E_PFINT_ICR0_PCI_EXCEPTION_MASK ; 
 int I40E_PFINT_ICR0_PE_CRITERR_MASK ; 
 int I40E_PFINT_ICR0_VFLR_MASK ; 
#define  I40E_RESET_CORER 130 
#define  I40E_RESET_EMPR 129 
#define  I40E_RESET_GLOBR 128 
 int IXL_ICR0_CRIT_ERR_MASK ; 
 int /*<<< orphan*/  IXL_PF_STATE_ADAPTER_RESETTING ; 
 int IXL_PF_STATE_MDD_PENDING ; 
 int IXL_PF_STATE_PF_CRIT_ERR ; 
 int IXL_PF_STATE_PF_RESET_REQ ; 
 int TRUE ; 
 int /*<<< orphan*/  atomic_set_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_iov_intr_deferred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_enable_intr0 (struct i40e_hw*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

int
ixl_msix_adminq(void *arg)
{
	struct ixl_pf	*pf = arg;
	struct i40e_hw	*hw = &pf->hw;
	device_t	dev = pf->dev;
	u32		reg, mask, rstat_reg;
	bool		do_task = FALSE;

	DDPRINTF(dev, "begin");

	++pf->admin_irq;

	reg = rd32(hw, I40E_PFINT_ICR0);
	/*
	 * For masking off interrupt causes that need to be handled before
	 * they can be re-enabled
	 */
	mask = rd32(hw, I40E_PFINT_ICR0_ENA);

	/* Check on the cause */
	if (reg & I40E_PFINT_ICR0_ADMINQ_MASK) {
		mask &= ~I40E_PFINT_ICR0_ENA_ADMINQ_MASK;
		do_task = TRUE;
	}

	if (reg & I40E_PFINT_ICR0_MAL_DETECT_MASK) {
		mask &= ~I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK;
		atomic_set_32(&pf->state, IXL_PF_STATE_MDD_PENDING);
		do_task = TRUE;
	}

	if (reg & I40E_PFINT_ICR0_GRST_MASK) {
		mask &= ~I40E_PFINT_ICR0_ENA_GRST_MASK;
		device_printf(dev, "Reset Requested!\n");
		rstat_reg = rd32(hw, I40E_GLGEN_RSTAT);
		rstat_reg = (rstat_reg & I40E_GLGEN_RSTAT_RESET_TYPE_MASK)
		    >> I40E_GLGEN_RSTAT_RESET_TYPE_SHIFT;
		device_printf(dev, "Reset type: ");
		switch (rstat_reg) {
		/* These others might be handled similarly to an EMPR reset */
		case I40E_RESET_CORER:
			printf("CORER\n");
			break;
		case I40E_RESET_GLOBR:
			printf("GLOBR\n");
			break;
		case I40E_RESET_EMPR:
			printf("EMPR\n");
			break;
		default:
			printf("POR\n");
			break;
		}
		/* overload admin queue task to check reset progress */
		atomic_set_int(&pf->state, IXL_PF_STATE_ADAPTER_RESETTING);
		do_task = TRUE;
	}

	/*
	 * PE / PCI / ECC exceptions are all handled in the same way:
	 * mask out these three causes, then request a PF reset
	 *
	 * TODO: I think at least ECC error requires a GLOBR, not PFR
	 */
	if (reg & I40E_PFINT_ICR0_ECC_ERR_MASK)
 		device_printf(dev, "ECC Error detected!\n");
	if (reg & I40E_PFINT_ICR0_PCI_EXCEPTION_MASK)
		device_printf(dev, "PCI Exception detected!\n");
	if (reg & I40E_PFINT_ICR0_PE_CRITERR_MASK)
		device_printf(dev, "Critical Protocol Engine Error detected!\n");
	/* Checks against the conditions above */
	if (reg & IXL_ICR0_CRIT_ERR_MASK) {
		mask &= ~IXL_ICR0_CRIT_ERR_MASK;
		atomic_set_32(&pf->state,
		    IXL_PF_STATE_PF_RESET_REQ | IXL_PF_STATE_PF_CRIT_ERR);
		do_task = TRUE;
	}

	// TODO: Linux driver never re-enables this interrupt once it has been detected
	// Then what is supposed to happen? A PF reset? Should it never happen?
	// TODO: Parse out this error into something human readable
	if (reg & I40E_PFINT_ICR0_HMC_ERR_MASK) {
		reg = rd32(hw, I40E_PFHMC_ERRORINFO);
		if (reg & I40E_PFHMC_ERRORINFO_ERROR_DETECTED_MASK) {
			device_printf(dev, "HMC Error detected!\n");
			device_printf(dev, "INFO 0x%08x\n", reg);
			reg = rd32(hw, I40E_PFHMC_ERRORDATA);
			device_printf(dev, "DATA 0x%08x\n", reg);
			wr32(hw, I40E_PFHMC_ERRORINFO, 0);
		}
	}

#ifdef PCI_IOV
	if (reg & I40E_PFINT_ICR0_VFLR_MASK) {
		mask &= ~I40E_PFINT_ICR0_ENA_VFLR_MASK;
		iflib_iov_intr_deferred(pf->vsi.ctx);
	}
#endif

	wr32(hw, I40E_PFINT_ICR0_ENA, mask);
	ixl_enable_intr0(hw);

	if (do_task)
		return (FILTER_SCHEDULE_THREAD);
	else
		return (FILTER_HANDLED);
}