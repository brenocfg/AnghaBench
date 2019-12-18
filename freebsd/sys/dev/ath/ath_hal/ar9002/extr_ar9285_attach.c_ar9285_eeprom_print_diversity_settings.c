#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_8__ {TYPE_3__* ah_eeprom; } ;
struct TYPE_6__ {int antdiv_ctl2; int antdiv_ctl1; } ;
struct TYPE_5__ {TYPE_2__ modalHeader; } ;
struct TYPE_7__ {TYPE_1__ ee_base; } ;
typedef  TYPE_2__ MODAL_EEP4K_HEADER ;
typedef  TYPE_3__ HAL_EEPROM_v4k ;

/* Variables and functions */
 TYPE_4__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/ * ar9285_lna_conf ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,char*,...) ; 

__attribute__((used)) static void
ar9285_eeprom_print_diversity_settings(struct ath_hal *ah)
{
	const HAL_EEPROM_v4k *ee = AH_PRIVATE(ah)->ah_eeprom;
	const MODAL_EEP4K_HEADER *pModal = &ee->ee_base.modalHeader;

	ath_hal_printf(ah, "[ath] AR9285 Main LNA config: %s\n",
	    ar9285_lna_conf[(pModal->antdiv_ctl2 >> 2) & 0x3]);
	ath_hal_printf(ah, "[ath] AR9285 Alt LNA config: %s\n",
	    ar9285_lna_conf[pModal->antdiv_ctl2 & 0x3]);
	ath_hal_printf(ah, "[ath] LNA diversity %s, Diversity %s\n",
	    ((pModal->antdiv_ctl1 & 0x1) ? "enabled" : "disabled"),
	    ((pModal->antdiv_ctl1 & 0x8) ? "enabled" : "disabled"));
}