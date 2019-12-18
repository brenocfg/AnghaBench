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
 int CMPCI_REG_BUS_AND_DSP_RESET ; 
 int CMPCI_REG_CH0_DIR ; 
 int CMPCI_REG_CH0_ENABLE ; 
 int CMPCI_REG_CH0_INTR_ENABLE ; 
 int CMPCI_REG_CH1_DIR ; 
 int CMPCI_REG_CH1_ENABLE ; 
 int CMPCI_REG_CH1_INTR_ENABLE ; 
 int /*<<< orphan*/  CMPCI_REG_FUNC_0 ; 
 int /*<<< orphan*/  CMPCI_REG_FUNC_1 ; 
 int /*<<< orphan*/  CMPCI_REG_INTR_CTRL ; 
 int /*<<< orphan*/  CMPCI_REG_MISC ; 
 int CMPCI_REG_N4SPK3D ; 
 int CMPCI_REG_SPDIF1_ENABLE ; 
 int CMPCI_REG_SPDIF_LOOP ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  cmi_clr4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmi_set4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cmi_init(struct sc_info *sc)
{
	/* Effect reset */
	cmi_set4(sc, CMPCI_REG_MISC, CMPCI_REG_BUS_AND_DSP_RESET);
	DELAY(100);
	cmi_clr4(sc, CMPCI_REG_MISC, CMPCI_REG_BUS_AND_DSP_RESET);

	/* Disable interrupts and channels */
	cmi_clr4(sc, CMPCI_REG_FUNC_0,
		 CMPCI_REG_CH0_ENABLE | CMPCI_REG_CH1_ENABLE);
	cmi_clr4(sc, CMPCI_REG_INTR_CTRL,
		 CMPCI_REG_CH0_INTR_ENABLE | CMPCI_REG_CH1_INTR_ENABLE);

	/* Configure DMA channels, ch0 = play, ch1 = capture */
	cmi_clr4(sc, CMPCI_REG_FUNC_0, CMPCI_REG_CH0_DIR);
	cmi_set4(sc, CMPCI_REG_FUNC_0, CMPCI_REG_CH1_DIR);

	/* Attempt to enable 4 Channel output */
	cmi_set4(sc, CMPCI_REG_MISC, CMPCI_REG_N4SPK3D);

	/* Disable SPDIF1 - not compatible with config */
	cmi_clr4(sc, CMPCI_REG_FUNC_1, CMPCI_REG_SPDIF1_ENABLE);
	cmi_clr4(sc, CMPCI_REG_FUNC_1, CMPCI_REG_SPDIF_LOOP);

	return 0;
}