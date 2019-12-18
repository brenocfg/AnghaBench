#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct athregrec {int val; } ;
struct TYPE_3__ {int ah_macVersion; int ah_macRev; } ;
struct TYPE_4__ {int chipnum; TYPE_1__ revs; } ;

/* Variables and functions */
#define  AR5210_DEFAULT 166 
#define  AR5210_PROD 165 
#define  AR5211_DEFAULT 164 
#define  AR5211_DEVID 163 
#define  AR5211_FPGA11B 162 
#define  AR5212_AR2313_REV8 161 
#define  AR5212_AR2315_REV6 160 
#define  AR5212_AR2315_REV7 159 
#define  AR5212_AR2317_REV1 158 
#define  AR5212_AR2317_REV2 157 
#define  AR5212_AR2413 156 
#define  AR5212_AR2417 155 
#define  AR5212_AR5312_REV2 154 
#define  AR5212_AR5312_REV7 153 
#define  AR5212_AR5413 152 
#define  AR5212_AR5424 151 
#define  AR5212_DEFAULT 150 
#define  AR5212_DEVID 149 
#define  AR5212_DEVID_0014 148 
#define  AR5212_DEVID_0015 147 
#define  AR5212_DEVID_0016 146 
#define  AR5212_DEVID_0017 145 
#define  AR5212_DEVID_0018 144 
#define  AR5212_DEVID_0019 143 
#define  AR5212_DEVID_FF19 142 
#define  AR5212_DEVID_IBM 141 
#define  AR5212_FPGA 140 
#define  AR5213_SREV_1_0 139 
#define  AR5213_SREV_REG 138 
#define  AR5311_DEVID 137 
#define  AR5416_DEVID_PCI 136 
#define  AR5416_DEVID_PCIE 135 
#define  AR9160_DEVID_PCI 134 
#define  AR9280_DEVID_PCI 133 
#define  AR9280_DEVID_PCIE 132 
#define  AR9285_DEVID_PCIE 131 
#define  AR9287_DEVID_PCI 130 
#define  AR9287_DEVID_PCIE 129 
#define  AR9300_DEVID_AR9330 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_2__ state ; 

__attribute__((used)) static void
opdevice(const struct athregrec *r)
{
	switch (r->val) {
	case AR5210_PROD:
	case AR5210_DEFAULT:
		state.chipnum = 5210;
		state.revs.ah_macVersion = 1;
		state.revs.ah_macRev = 0;
		break;
	case AR5211_DEVID:
	case AR5311_DEVID:
	case AR5211_DEFAULT:
	case AR5211_FPGA11B:
		state.chipnum = 5211;
		state.revs.ah_macVersion = 2;
		state.revs.ah_macRev = 0;
		break;
	/* AR5212 */
	case AR5212_DEFAULT:
	case AR5212_DEVID:
	case AR5212_FPGA:
	case AR5212_DEVID_IBM:
	case AR5212_AR5312_REV2:
	case AR5212_AR5312_REV7:
	case AR5212_AR2313_REV8:
	case AR5212_AR2315_REV6:
	case AR5212_AR2315_REV7:
	case AR5212_AR2317_REV1:
	case AR5212_AR2317_REV2:

	/* AR5212 compatible devid's also attach to 5212 */
	case AR5212_DEVID_0014:
	case AR5212_DEVID_0015:
	case AR5212_DEVID_0016:
	case AR5212_DEVID_0017:
	case AR5212_DEVID_0018:
	case AR5212_DEVID_0019:
	case AR5212_AR2413:
	case AR5212_AR5413:
	case AR5212_AR5424:
	case AR5212_AR2417:
	case AR5212_DEVID_FF19:
		state.chipnum = 5212;
		state.revs.ah_macVersion = 4;
		state.revs.ah_macRev = 5;
		break;

	/* AR5213 */
	case AR5213_SREV_1_0:
	case AR5213_SREV_REG:
		state.chipnum = 5213;
		state.revs.ah_macVersion = 5;
		state.revs.ah_macRev = 9;
		break;

	/* AR5416 compatible devid's  */
	case AR5416_DEVID_PCI:
	case AR5416_DEVID_PCIE:
	case AR9160_DEVID_PCI:
	case AR9280_DEVID_PCI:
	case AR9280_DEVID_PCIE:
	case AR9285_DEVID_PCIE:
	case AR9287_DEVID_PCI:
	case AR9287_DEVID_PCIE:
	case AR9300_DEVID_AR9330:
		state.chipnum = 5416;
		state.revs.ah_macVersion = 13;
		state.revs.ah_macRev = 8;
		break;
	default:
		printf("Unknown device id 0x%x\n", r->val);
		exit(-1);
	}
}