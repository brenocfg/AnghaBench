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
struct gsw_mt753x {int (* mmd_read ) (struct gsw_mt753x*,int,int,int) ;int /*<<< orphan*/  (* mii_write ) (struct gsw_mt753x*,int,int,int) ;int /*<<< orphan*/  (* mmd_write ) (struct gsw_mt753x*,int,int,int,int) ;} ;

/* Variables and functions */
 int DESCRAMBLER_CLEAR_EN ; 
 int DSP_CH ; 
 int DSP_NOD_ADDR ; 
 int PHY_DEV1E ; 
 int PHY_DEV1E_REG_189 ; 
 int stub1 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub10 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub11 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub12 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub13 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub14 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct gsw_mt753x*,int,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct gsw_mt753x*,int,int,int,int) ; 
 int /*<<< orphan*/  stub5 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub7 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct gsw_mt753x*,int,int,int) ; 

__attribute__((used)) static void mt7531_eee_setting(struct gsw_mt753x *gsw, u32 port)
{
	u32 tr_reg_control;
	u32 val;

	/* Disable generate signal to clear the scramble_lock when lpi mode */
	val = gsw->mmd_read(gsw, port, PHY_DEV1E, PHY_DEV1E_REG_189);
	val &= ~DESCRAMBLER_CLEAR_EN;
	gsw->mmd_write(gsw, port, PHY_DEV1E, PHY_DEV1E_REG_189, val);

	/* roll back CR*/
	gsw->mii_write(gsw, port, 0x1f, 0x52b5);
	gsw->mmd_write(gsw, port, 0x1e, 0x2d1, 0);
	tr_reg_control = (1 << 15) | (0 << 13) | (DSP_CH << 11) |
			 (DSP_NOD_ADDR << 7) | (0x8 << 1);
	gsw->mii_write(gsw, port, 17, 0x1b);
	gsw->mii_write(gsw, port, 18, 0);
	gsw->mii_write(gsw, port, 16, tr_reg_control);
	tr_reg_control = (1 << 15) | (0 << 13) | (DSP_CH << 11) |
			 (DSP_NOD_ADDR << 7) | (0xf << 1);
	gsw->mii_write(gsw, port, 17, 0);
	gsw->mii_write(gsw, port, 18, 0);
	gsw->mii_write(gsw, port, 16, tr_reg_control);

	tr_reg_control = (1 << 15) | (0 << 13) | (DSP_CH << 11) |
			 (DSP_NOD_ADDR << 7) | (0x10 << 1);
	gsw->mii_write(gsw, port, 17, 0x500);
	gsw->mii_write(gsw, port, 18, 0);
	gsw->mii_write(gsw, port, 16, tr_reg_control);
	gsw->mii_write(gsw, port, 0x1f, 0);
}