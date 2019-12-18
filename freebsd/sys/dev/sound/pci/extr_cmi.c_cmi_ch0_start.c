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
struct sc_chinfo {int dma_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPCI_REG_CH0_ENABLE ; 
 int /*<<< orphan*/  CMPCI_REG_CH0_INTR_ENABLE ; 
 int /*<<< orphan*/  CMPCI_REG_DMA0_BASE ; 
 int /*<<< orphan*/  CMPCI_REG_FUNC_0 ; 
 int /*<<< orphan*/  CMPCI_REG_INTR_CTRL ; 
 int /*<<< orphan*/  cmi_dma_prog (struct sc_info*,struct sc_chinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmi_set4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmi_ch0_start(struct sc_info *sc, struct sc_chinfo *ch)
{
	cmi_dma_prog(sc, ch, CMPCI_REG_DMA0_BASE);

	cmi_set4(sc, CMPCI_REG_FUNC_0, CMPCI_REG_CH0_ENABLE);
	cmi_set4(sc, CMPCI_REG_INTR_CTRL,
		 CMPCI_REG_CH0_INTR_ENABLE);

	ch->dma_active = 1;
}