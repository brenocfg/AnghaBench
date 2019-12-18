#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,int,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub10 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub11 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub13 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub14 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub15 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub16 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub17 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub18 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub19 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub20 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub21 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub22 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub23 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub24 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub25 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub26 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub27 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub28 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub29 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub30 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub31 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub32 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*,int,int) ; 

s32 e1000_phy_init_script_igp3(struct e1000_hw *hw)
{
	DEBUGOUT("Running IGP 3 PHY init script\n");

	/* PHY init IGP 3 */
	/* Enable rise/fall, 10-mode work in class-A */
	hw->phy.ops.write_reg(hw, 0x2F5B, 0x9018);
	/* Remove all caps from Replica path filter */
	hw->phy.ops.write_reg(hw, 0x2F52, 0x0000);
	/* Bias trimming for ADC, AFE and Driver (Default) */
	hw->phy.ops.write_reg(hw, 0x2FB1, 0x8B24);
	/* Increase Hybrid poly bias */
	hw->phy.ops.write_reg(hw, 0x2FB2, 0xF8F0);
	/* Add 4% to Tx amplitude in Gig mode */
	hw->phy.ops.write_reg(hw, 0x2010, 0x10B0);
	/* Disable trimming (TTT) */
	hw->phy.ops.write_reg(hw, 0x2011, 0x0000);
	/* Poly DC correction to 94.6% + 2% for all channels */
	hw->phy.ops.write_reg(hw, 0x20DD, 0x249A);
	/* ABS DC correction to 95.9% */
	hw->phy.ops.write_reg(hw, 0x20DE, 0x00D3);
	/* BG temp curve trim */
	hw->phy.ops.write_reg(hw, 0x28B4, 0x04CE);
	/* Increasing ADC OPAMP stage 1 currents to max */
	hw->phy.ops.write_reg(hw, 0x2F70, 0x29E4);
	/* Force 1000 ( required for enabling PHY regs configuration) */
	hw->phy.ops.write_reg(hw, 0x0000, 0x0140);
	/* Set upd_freq to 6 */
	hw->phy.ops.write_reg(hw, 0x1F30, 0x1606);
	/* Disable NPDFE */
	hw->phy.ops.write_reg(hw, 0x1F31, 0xB814);
	/* Disable adaptive fixed FFE (Default) */
	hw->phy.ops.write_reg(hw, 0x1F35, 0x002A);
	/* Enable FFE hysteresis */
	hw->phy.ops.write_reg(hw, 0x1F3E, 0x0067);
	/* Fixed FFE for short cable lengths */
	hw->phy.ops.write_reg(hw, 0x1F54, 0x0065);
	/* Fixed FFE for medium cable lengths */
	hw->phy.ops.write_reg(hw, 0x1F55, 0x002A);
	/* Fixed FFE for long cable lengths */
	hw->phy.ops.write_reg(hw, 0x1F56, 0x002A);
	/* Enable Adaptive Clip Threshold */
	hw->phy.ops.write_reg(hw, 0x1F72, 0x3FB0);
	/* AHT reset limit to 1 */
	hw->phy.ops.write_reg(hw, 0x1F76, 0xC0FF);
	/* Set AHT master delay to 127 msec */
	hw->phy.ops.write_reg(hw, 0x1F77, 0x1DEC);
	/* Set scan bits for AHT */
	hw->phy.ops.write_reg(hw, 0x1F78, 0xF9EF);
	/* Set AHT Preset bits */
	hw->phy.ops.write_reg(hw, 0x1F79, 0x0210);
	/* Change integ_factor of channel A to 3 */
	hw->phy.ops.write_reg(hw, 0x1895, 0x0003);
	/* Change prop_factor of channels BCD to 8 */
	hw->phy.ops.write_reg(hw, 0x1796, 0x0008);
	/* Change cg_icount + enable integbp for channels BCD */
	hw->phy.ops.write_reg(hw, 0x1798, 0xD008);
	/* Change cg_icount + enable integbp + change prop_factor_master
	 * to 8 for channel A
	 */
	hw->phy.ops.write_reg(hw, 0x1898, 0xD918);
	/* Disable AHT in Slave mode on channel A */
	hw->phy.ops.write_reg(hw, 0x187A, 0x0800);
	/* Enable LPLU and disable AN to 1000 in non-D0a states,
	 * Enable SPD+B2B
	 */
	hw->phy.ops.write_reg(hw, 0x0019, 0x008D);
	/* Enable restart AN on an1000_dis change */
	hw->phy.ops.write_reg(hw, 0x001B, 0x2080);
	/* Enable wh_fifo read clock in 10/100 modes */
	hw->phy.ops.write_reg(hw, 0x0014, 0x0045);
	/* Restart AN, Speed selection is 1000 */
	hw->phy.ops.write_reg(hw, 0x0000, 0x1340);

	return E1000_SUCCESS;
}