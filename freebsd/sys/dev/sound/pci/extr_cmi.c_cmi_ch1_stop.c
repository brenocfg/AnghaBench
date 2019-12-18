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
typedef  scalar_t__ u_int32_t ;
struct sc_info {int dummy; } ;
struct sc_chinfo {scalar_t__ dma_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPCI_REG_CH1_ENABLE ; 
 int /*<<< orphan*/  CMPCI_REG_CH1_INTR_ENABLE ; 
 int /*<<< orphan*/  CMPCI_REG_CH1_RESET ; 
 int /*<<< orphan*/  CMPCI_REG_FUNC_0 ; 
 int /*<<< orphan*/  CMPCI_REG_INTR_CTRL ; 
 int /*<<< orphan*/  cmi_clr4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmi_set4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
cmi_ch1_stop(struct sc_info *sc, struct sc_chinfo *ch)
{
	u_int32_t r = ch->dma_active;

	cmi_clr4(sc, CMPCI_REG_INTR_CTRL, CMPCI_REG_CH1_INTR_ENABLE);
	cmi_clr4(sc, CMPCI_REG_FUNC_0, CMPCI_REG_CH1_ENABLE);
        cmi_set4(sc, CMPCI_REG_FUNC_0, CMPCI_REG_CH1_RESET);
        cmi_clr4(sc, CMPCI_REG_FUNC_0, CMPCI_REG_CH1_RESET);
	ch->dma_active = 0;
	return r;
}