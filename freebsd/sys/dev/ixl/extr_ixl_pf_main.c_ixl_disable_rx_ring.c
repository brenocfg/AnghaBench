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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ixl_pf_qtag {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct i40e_hw hw; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I40E_QRX_ENA (int /*<<< orphan*/ ) ; 
 int I40E_QRX_ENA_QENA_REQ_MASK ; 
 int I40E_QRX_ENA_QENA_STAT_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 
 int /*<<< orphan*/  ixl_pf_qidx_from_vsi_qidx (struct ixl_pf_qtag*,int /*<<< orphan*/ ) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

int
ixl_disable_rx_ring(struct ixl_pf *pf, struct ixl_pf_qtag *qtag, u16 vsi_qidx)
{
	struct i40e_hw	*hw = &pf->hw;
	int		error = 0;
	u32		reg;
	u16		pf_qidx;

	pf_qidx = ixl_pf_qidx_from_vsi_qidx(qtag, vsi_qidx);

	reg = rd32(hw, I40E_QRX_ENA(pf_qidx));
	reg &= ~I40E_QRX_ENA_QENA_REQ_MASK;
	wr32(hw, I40E_QRX_ENA(pf_qidx), reg);
	/* Verify the disable took */
	for (int j = 0; j < 10; j++) {
		reg = rd32(hw, I40E_QRX_ENA(pf_qidx));
		if (!(reg & I40E_QRX_ENA_QENA_STAT_MASK))
			break;
		i40e_msec_delay(10);
	}
	if (reg & I40E_QRX_ENA_QENA_STAT_MASK) {
		device_printf(pf->dev, "RX queue %d still enabled!\n",
		    pf_qidx);
		error = ETIMEDOUT;
	}

	return (error);
}