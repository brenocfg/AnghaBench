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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int IXGBE_DCA_RXCTRL_DATA_WRO_EN ; 
 int IXGBE_DCA_RXCTRL_DESC_RRO_EN ; 
 int IXGBE_DCA_RXCTRL_HEAD_WRO_EN ; 
 int IXGBE_DCA_TXCTRL_DATA_RRO_EN ; 
 int IXGBE_DCA_TXCTRL_DESC_RRO_EN ; 
 int IXGBE_DCA_TXCTRL_DESC_WRO_EN ; 
 int IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT ; 
 int IXGBE_SRRCTL_BSIZEPKT_SHIFT ; 
 int /*<<< orphan*/  IXGBE_VFDCA_RXCTRL (int) ; 
 int /*<<< orphan*/  IXGBE_VFDCA_TXCTRL (int) ; 
 int /*<<< orphan*/  IXGBE_VFPSRTYPE ; 
 int /*<<< orphan*/  IXGBE_VFRDH (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDT (int) ; 
 int /*<<< orphan*/  IXGBE_VFRXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VFSRRCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDH (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDT (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDWBAH (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDWBAL (int) ; 
 int /*<<< orphan*/  IXGBE_VFTXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_virt_clr_reg(struct ixgbe_hw *hw)
{
	int i;
	u32 vfsrrctl;
	u32 vfdca_rxctrl;
	u32 vfdca_txctrl;

	/* VRSRRCTL default values (BSIZEPACKET = 2048, BSIZEHEADER = 256) */
	vfsrrctl = 0x100 << IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT;
	vfsrrctl |= 0x800 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;

	/* DCA_RXCTRL default value */
	vfdca_rxctrl = IXGBE_DCA_RXCTRL_DESC_RRO_EN |
		       IXGBE_DCA_RXCTRL_DATA_WRO_EN |
		       IXGBE_DCA_RXCTRL_HEAD_WRO_EN;

	/* DCA_TXCTRL default value */
	vfdca_txctrl = IXGBE_DCA_TXCTRL_DESC_RRO_EN |
		       IXGBE_DCA_TXCTRL_DESC_WRO_EN |
		       IXGBE_DCA_TXCTRL_DATA_RRO_EN;

	IXGBE_WRITE_REG(hw, IXGBE_VFPSRTYPE, 0);

	for (i = 0; i < 7; i++) {
		IXGBE_WRITE_REG(hw, IXGBE_VFRDH(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFRDT(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFSRRCTL(i), vfsrrctl);
		IXGBE_WRITE_REG(hw, IXGBE_VFTDH(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFTDT(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFTDWBAH(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFTDWBAL(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFDCA_RXCTRL(i), vfdca_rxctrl);
		IXGBE_WRITE_REG(hw, IXGBE_VFDCA_TXCTRL(i), vfdca_txctrl);
	}

	IXGBE_WRITE_FLUSH(hw);
}