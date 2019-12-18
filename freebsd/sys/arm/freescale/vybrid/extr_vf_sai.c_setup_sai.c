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
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_TCR1 ; 
 int /*<<< orphan*/  I2S_TCR2 ; 
 int /*<<< orphan*/  I2S_TCR3 ; 
 int /*<<< orphan*/  I2S_TCR4 ; 
 int /*<<< orphan*/  I2S_TCR5 ; 
 int /*<<< orphan*/  I2S_TCSR ; 
 int READ4 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int TCR1_TFW_S ; 
 int TCR2_BCD ; 
 int TCR2_BCP ; 
 int TCR2_MSEL_M ; 
 int TCR2_MSEL_S ; 
 int TCR3_TCE ; 
 int TCR4_FRSZ_M ; 
 int TCR4_FRSZ_S ; 
 int TCR4_FSD ; 
 int TCR4_FSE ; 
 int TCR4_FSP ; 
 int TCR4_MF ; 
 int TCR4_SYWD_M ; 
 int TCR4_SYWD_S ; 
 int TCR5_FBT_M ; 
 int TCR5_FBT_S ; 
 int TCR5_W0W_M ; 
 int TCR5_W0W_S ; 
 int TCR5_WNW_M ; 
 int TCR5_WNW_S ; 
 int TCSR_BCE ; 
 int TCSR_FRDE ; 
 int TCSR_TE ; 
 int /*<<< orphan*/  WRITE4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sai_configure_clock (struct sc_info*) ; 

__attribute__((used)) static void
setup_sai(struct sc_info *sc)
{
	int reg;

	/*
	 * TCR/RCR registers must not be altered when TCSR[TE] is set.
	 */

	reg = READ4(sc, I2S_TCSR);
	reg &= ~(TCSR_BCE | TCSR_TE | TCSR_FRDE);
	WRITE4(sc, I2S_TCSR, reg);

	reg = READ4(sc, I2S_TCR3);
	reg &= ~(TCR3_TCE);
	WRITE4(sc, I2S_TCR3, reg);

	reg = (64 << TCR1_TFW_S);
	WRITE4(sc, I2S_TCR1, reg);

	reg = READ4(sc, I2S_TCR2);
	reg &= ~(TCR2_MSEL_M << TCR2_MSEL_S);
	reg |= (1 << TCR2_MSEL_S);
	reg |= (TCR2_BCP | TCR2_BCD);
	WRITE4(sc, I2S_TCR2, reg);

	sai_configure_clock(sc);

	reg = READ4(sc, I2S_TCR3);
	reg |= (TCR3_TCE);
	WRITE4(sc, I2S_TCR3, reg);

	/* Configure to 32-bit I2S mode */
	reg = READ4(sc, I2S_TCR4);
	reg &= ~(TCR4_FRSZ_M << TCR4_FRSZ_S);
	reg |= (1 << TCR4_FRSZ_S); /* 2 words per frame */
	reg &= ~(TCR4_SYWD_M << TCR4_SYWD_S);
	reg |= (23 << TCR4_SYWD_S);
	reg |= (TCR4_MF | TCR4_FSE | TCR4_FSP | TCR4_FSD);
	WRITE4(sc, I2S_TCR4, reg);

	reg = READ4(sc, I2S_TCR5);
	reg &= ~(TCR5_W0W_M << TCR5_W0W_S);
	reg |= (23 << TCR5_W0W_S);
	reg &= ~(TCR5_WNW_M << TCR5_WNW_S);
	reg |= (23 << TCR5_WNW_S);
	reg &= ~(TCR5_FBT_M << TCR5_FBT_S);
	reg |= (31 << TCR5_FBT_S);
	WRITE4(sc, I2S_TCR5, reg);

	/* Enable transmitter */
	reg = READ4(sc, I2S_TCSR);
	reg |= (TCSR_BCE | TCSR_TE | TCSR_FRDE);
	reg |= (1 << 10); /* FEIE */
	WRITE4(sc, I2S_TCSR, reg);
}