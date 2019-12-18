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
struct iwm_softc {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ mqrx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IWM_CSR_RESET ; 
 int /*<<< orphan*/  IWM_CSR_RESET_REG_FLAG_SW_RESET ; 
 int /*<<< orphan*/  IWM_UREG_CHICK ; 
 int /*<<< orphan*/  IWM_UREG_CHICK_MSI_ENABLE ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwm_apm_init (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_check_rfkill (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_enable_rfkill_int (struct iwm_softc*) ; 
 int iwm_prepare_card_hw (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_write_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
iwm_start_hw(struct iwm_softc *sc)
{
	int error;

	if ((error = iwm_prepare_card_hw(sc)) != 0)
		return error;

	/* Reset the entire device */
	IWM_WRITE(sc, IWM_CSR_RESET, IWM_CSR_RESET_REG_FLAG_SW_RESET);
	DELAY(5000);

	if ((error = iwm_apm_init(sc)) != 0)
		return error;

	/* On newer chipsets MSI is disabled by default. */
	if (sc->cfg->mqrx_supported)
		iwm_write_prph(sc, IWM_UREG_CHICK, IWM_UREG_CHICK_MSI_ENABLE);

	iwm_enable_rfkill_int(sc);
	iwm_check_rfkill(sc);

	return 0;
}