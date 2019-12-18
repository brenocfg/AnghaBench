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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_BPRC ; 
 int /*<<< orphan*/  E1000_BPTC ; 
 int /*<<< orphan*/  E1000_COLC ; 
 int /*<<< orphan*/  E1000_CRCERRS ; 
 int /*<<< orphan*/  E1000_DC ; 
 int /*<<< orphan*/  E1000_ECOL ; 
 int /*<<< orphan*/  E1000_FCRUC ; 
 int /*<<< orphan*/  E1000_GORCH ; 
 int /*<<< orphan*/  E1000_GORCL ; 
 int /*<<< orphan*/  E1000_GOTCH ; 
 int /*<<< orphan*/  E1000_GOTCL ; 
 int /*<<< orphan*/  E1000_GPRC ; 
 int /*<<< orphan*/  E1000_GPTC ; 
 int /*<<< orphan*/  E1000_LATECOL ; 
 int /*<<< orphan*/  E1000_MCC ; 
 int /*<<< orphan*/  E1000_MPC ; 
 int /*<<< orphan*/  E1000_MPRC ; 
 int /*<<< orphan*/  E1000_MPTC ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_RFC ; 
 int /*<<< orphan*/  E1000_RJC ; 
 int /*<<< orphan*/  E1000_RLEC ; 
 int /*<<< orphan*/  E1000_RNBC ; 
 int /*<<< orphan*/  E1000_ROC ; 
 int /*<<< orphan*/  E1000_RUC ; 
 int /*<<< orphan*/  E1000_SCC ; 
 int /*<<< orphan*/  E1000_SEC ; 
 int /*<<< orphan*/  E1000_SYMERRS ; 
 int /*<<< orphan*/  E1000_TORH ; 
 int /*<<< orphan*/  E1000_TORL ; 
 int /*<<< orphan*/  E1000_TOTH ; 
 int /*<<< orphan*/  E1000_TOTL ; 
 int /*<<< orphan*/  E1000_TPR ; 
 int /*<<< orphan*/  E1000_TPT ; 
 int /*<<< orphan*/  E1000_XOFFRXC ; 
 int /*<<< orphan*/  E1000_XOFFTXC ; 
 int /*<<< orphan*/  E1000_XONRXC ; 
 int /*<<< orphan*/  E1000_XONTXC ; 

void e1000_clear_hw_cntrs_base_generic(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_clear_hw_cntrs_base_generic");

	E1000_READ_REG(hw, E1000_CRCERRS);
	E1000_READ_REG(hw, E1000_SYMERRS);
	E1000_READ_REG(hw, E1000_MPC);
	E1000_READ_REG(hw, E1000_SCC);
	E1000_READ_REG(hw, E1000_ECOL);
	E1000_READ_REG(hw, E1000_MCC);
	E1000_READ_REG(hw, E1000_LATECOL);
	E1000_READ_REG(hw, E1000_COLC);
	E1000_READ_REG(hw, E1000_DC);
	E1000_READ_REG(hw, E1000_SEC);
	E1000_READ_REG(hw, E1000_RLEC);
	E1000_READ_REG(hw, E1000_XONRXC);
	E1000_READ_REG(hw, E1000_XONTXC);
	E1000_READ_REG(hw, E1000_XOFFRXC);
	E1000_READ_REG(hw, E1000_XOFFTXC);
	E1000_READ_REG(hw, E1000_FCRUC);
	E1000_READ_REG(hw, E1000_GPRC);
	E1000_READ_REG(hw, E1000_BPRC);
	E1000_READ_REG(hw, E1000_MPRC);
	E1000_READ_REG(hw, E1000_GPTC);
	E1000_READ_REG(hw, E1000_GORCL);
	E1000_READ_REG(hw, E1000_GORCH);
	E1000_READ_REG(hw, E1000_GOTCL);
	E1000_READ_REG(hw, E1000_GOTCH);
	E1000_READ_REG(hw, E1000_RNBC);
	E1000_READ_REG(hw, E1000_RUC);
	E1000_READ_REG(hw, E1000_RFC);
	E1000_READ_REG(hw, E1000_ROC);
	E1000_READ_REG(hw, E1000_RJC);
	E1000_READ_REG(hw, E1000_TORL);
	E1000_READ_REG(hw, E1000_TORH);
	E1000_READ_REG(hw, E1000_TOTL);
	E1000_READ_REG(hw, E1000_TOTH);
	E1000_READ_REG(hw, E1000_TPR);
	E1000_READ_REG(hw, E1000_TPT);
	E1000_READ_REG(hw, E1000_MPTC);
	E1000_READ_REG(hw, E1000_BPTC);
}