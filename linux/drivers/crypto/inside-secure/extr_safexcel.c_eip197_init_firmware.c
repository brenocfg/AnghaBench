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
struct TYPE_2__ {int pes; } ;
struct safexcel_crypto_priv {TYPE_1__ config; } ;

/* Variables and functions */
 int EIP197_NUM_OF_SCRATCH_BLOCKS ; 
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_PE_ICE_FPP_CTRL (int) ; 
 scalar_t__ EIP197_PE_ICE_PPTF_CTRL (int) ; 
 scalar_t__ EIP197_PE_ICE_PUE_CTRL (int) ; 
 scalar_t__ EIP197_PE_ICE_PUTF_CTRL (int) ; 
 scalar_t__ EIP197_PE_ICE_RAM_CTRL (int) ; 
 int EIP197_PE_ICE_RAM_CTRL_FPP_PROG_EN ; 
 scalar_t__ EIP197_PE_ICE_SCRATCH_CTRL (int) ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_ACCESS ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_TIMER ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_SCRATCH_ACCESS ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_TIMER_EN ; 
 scalar_t__ EIP197_PE_ICE_SCRATCH_RAM (int) ; 
 int EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR ; 
 int EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR ; 
 int EIP197_PE_ICE_x_CTRL_SW_RESET ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void eip197_init_firmware(struct safexcel_crypto_priv *priv)
{
	int pe, i;
	u32 val;

	for (pe = 0; pe < priv->config.pes; pe++) {
		/* Configure the token FIFO's */
		writel(3, EIP197_PE(priv) + EIP197_PE_ICE_PUTF_CTRL(pe));
		writel(0, EIP197_PE(priv) + EIP197_PE_ICE_PPTF_CTRL(pe));

		/* Clear the ICE scratchpad memory */
		val = readl(EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_CTRL(pe));
		val |= EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_TIMER |
		       EIP197_PE_ICE_SCRATCH_CTRL_TIMER_EN |
		       EIP197_PE_ICE_SCRATCH_CTRL_SCRATCH_ACCESS |
		       EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_ACCESS;
		writel(val, EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_CTRL(pe));

		/* clear the scratchpad RAM using 32 bit writes only */
		for (i = 0; i < EIP197_NUM_OF_SCRATCH_BLOCKS; i++)
			writel(0, EIP197_PE(priv) +
				  EIP197_PE_ICE_SCRATCH_RAM(pe) + (i << 2));

		/* Reset the IFPP engine to make its program mem accessible */
		writel(EIP197_PE_ICE_x_CTRL_SW_RESET |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR,
		       EIP197_PE(priv) + EIP197_PE_ICE_FPP_CTRL(pe));

		/* Reset the IPUE engine to make its program mem accessible */
		writel(EIP197_PE_ICE_x_CTRL_SW_RESET |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR,
		       EIP197_PE(priv) + EIP197_PE_ICE_PUE_CTRL(pe));

		/* Enable access to all IFPP program memories */
		writel(EIP197_PE_ICE_RAM_CTRL_FPP_PROG_EN,
		       EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));
	}

}