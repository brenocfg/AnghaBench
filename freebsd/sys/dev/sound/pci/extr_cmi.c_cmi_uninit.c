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
struct sc_info {int /*<<< orphan*/ * mpu_intr; scalar_t__ mpu; } ;

/* Variables and functions */
 int CMPCI_REG_CH0_ENABLE ; 
 int CMPCI_REG_CH0_INTR_ENABLE ; 
 int CMPCI_REG_CH1_ENABLE ; 
 int CMPCI_REG_CH1_INTR_ENABLE ; 
 int /*<<< orphan*/  CMPCI_REG_FUNC_0 ; 
 int /*<<< orphan*/  CMPCI_REG_FUNC_1 ; 
 int /*<<< orphan*/  CMPCI_REG_INTR_CTRL ; 
 int CMPCI_REG_TDMA_INTR_ENABLE ; 
 int CMPCI_REG_UART_ENABLE ; 
 int /*<<< orphan*/  cmi_clr4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cmi_uninit(struct sc_info *sc)
{
	/* Disable interrupts and channels */
	cmi_clr4(sc, CMPCI_REG_INTR_CTRL,
		 CMPCI_REG_CH0_INTR_ENABLE |
		 CMPCI_REG_CH1_INTR_ENABLE |
		 CMPCI_REG_TDMA_INTR_ENABLE);
	cmi_clr4(sc, CMPCI_REG_FUNC_0,
		 CMPCI_REG_CH0_ENABLE | CMPCI_REG_CH1_ENABLE);
	cmi_clr4(sc, CMPCI_REG_FUNC_1, CMPCI_REG_UART_ENABLE);

	if( sc->mpu )
		sc->mpu_intr = NULL;
}