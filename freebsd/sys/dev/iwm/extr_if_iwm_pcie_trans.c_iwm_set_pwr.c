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
struct iwm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_APMG_PS_CTRL_MSK_PWR_SRC ; 
 int /*<<< orphan*/  IWM_APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  IWM_APMG_PS_CTRL_VAL_PWR_SRC_VMAIN ; 
 int /*<<< orphan*/  iwm_set_bits_mask_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iwm_set_pwr(struct iwm_softc *sc)
{
	iwm_set_bits_mask_prph(sc, IWM_APMG_PS_CTRL_REG,
	    IWM_APMG_PS_CTRL_VAL_PWR_SRC_VMAIN, ~IWM_APMG_PS_CTRL_MSK_PWR_SRC);
}