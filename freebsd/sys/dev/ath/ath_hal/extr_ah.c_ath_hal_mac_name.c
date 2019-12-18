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
struct ath_hal {int ah_macVersion; int /*<<< orphan*/  ah_macRev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_ispcie; } ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
#define  AR_SREV_2417 153 
#define  AR_SREV_2425 152 
 int /*<<< orphan*/  AR_SREV_REVISION_AR9580_10 ; 
#define  AR_SREV_VERSION_AR9330 151 
#define  AR_SREV_VERSION_AR9340 150 
#define  AR_SREV_VERSION_AR9380 149 
#define  AR_SREV_VERSION_AR9460 148 
#define  AR_SREV_VERSION_AR9485 147 
#define  AR_SREV_VERSION_COBRA 146 
#define  AR_SREV_VERSION_CONDOR 145 
#define  AR_SREV_VERSION_CRETE 144 
#define  AR_SREV_VERSION_EAGLE 143 
#define  AR_SREV_VERSION_GRIFFIN 142 
#define  AR_SREV_VERSION_MAUI_1 141 
#define  AR_SREV_VERSION_MAUI_2 140 
#define  AR_SREV_VERSION_OAHU 139 
#define  AR_SREV_VERSION_QCA9530 138 
#define  AR_SREV_VERSION_QCA9550 137 
#define  AR_SREV_VERSION_QCA9565 136 
#define  AR_SREV_VERSION_VENICE 135 
#define  AR_XSREV_VERSION_HOWL 134 
#define  AR_XSREV_VERSION_KITE 133 
#define  AR_XSREV_VERSION_KIWI 132 
#define  AR_XSREV_VERSION_MERLIN 131 
#define  AR_XSREV_VERSION_OWL_PCI 130 
#define  AR_XSREV_VERSION_OWL_PCIE 129 
#define  AR_XSREV_VERSION_SOWL 128 

const char *
ath_hal_mac_name(struct ath_hal *ah)
{
	switch (ah->ah_macVersion) {
	case AR_SREV_VERSION_CRETE:
	case AR_SREV_VERSION_MAUI_1:
		return "AR5210";
	case AR_SREV_VERSION_MAUI_2:
	case AR_SREV_VERSION_OAHU:
		return "AR5211";
	case AR_SREV_VERSION_VENICE:
		return "AR5212";
	case AR_SREV_VERSION_GRIFFIN:
		return "AR2413";
	case AR_SREV_VERSION_CONDOR:
		return "AR5424";
	case AR_SREV_VERSION_EAGLE:
		return "AR5413";
	case AR_SREV_VERSION_COBRA:
		return "AR2415";
	case AR_SREV_2425:	/* Swan */
		return "AR2425";
	case AR_SREV_2417:	/* Nala */
		return "AR2417";
	case AR_XSREV_VERSION_OWL_PCI:
		return "AR5416";
	case AR_XSREV_VERSION_OWL_PCIE:
		return "AR5418";
	case AR_XSREV_VERSION_HOWL:
		return "AR9130";
	case AR_XSREV_VERSION_SOWL:
		return "AR9160";
	case AR_XSREV_VERSION_MERLIN:
		if (AH_PRIVATE(ah)->ah_ispcie)
			return "AR9280";
		return "AR9220";
	case AR_XSREV_VERSION_KITE:
		return "AR9285";
	case AR_XSREV_VERSION_KIWI:
		if (AH_PRIVATE(ah)->ah_ispcie)
			return "AR9287";
		return "AR9227";
	case AR_SREV_VERSION_AR9380:
		if (ah->ah_macRev >= AR_SREV_REVISION_AR9580_10)
			return "AR9580";
		return "AR9380";
	case AR_SREV_VERSION_AR9460:
		return "AR9460";
	case AR_SREV_VERSION_AR9330:
		return "AR9330";
	case AR_SREV_VERSION_AR9340:
		return "AR9340";
	case AR_SREV_VERSION_QCA9550:
		return "QCA9550";
	case AR_SREV_VERSION_AR9485:
		return "AR9485";
	case AR_SREV_VERSION_QCA9565:
		return "QCA9565";
	case AR_SREV_VERSION_QCA9530:
		return "QCA9530";
	}
	return "????";
}