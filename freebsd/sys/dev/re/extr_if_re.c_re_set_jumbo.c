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
struct rl_softc {int /*<<< orphan*/  rl_dev; TYPE_1__* rl_hwrev; int /*<<< orphan*/  rl_cfg4; int /*<<< orphan*/  rl_cfg3; } ;
struct TYPE_2__ {int rl_rev; } ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int RL_CFG3_JUMBO_EN0 ; 
 int RL_CFG4_JUMBO_EN1 ; 
 int /*<<< orphan*/  RL_EECMD ; 
 int RL_EEMODE_OFF ; 
 int RL_EEMODE_WRITECFG ; 
#define  RL_HWREV_8168DP 129 
#define  RL_HWREV_8168E 128 
 int RL_HWREV_8168E_VL ; 
 int /*<<< orphan*/  pci_set_max_read_req (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
re_set_jumbo(struct rl_softc *sc, int jumbo)
{

	if (sc->rl_hwrev->rl_rev == RL_HWREV_8168E_VL) {
		pci_set_max_read_req(sc->rl_dev, 4096);
		return;
	}

	CSR_WRITE_1(sc, RL_EECMD, RL_EEMODE_WRITECFG);
	if (jumbo != 0) {
		CSR_WRITE_1(sc, sc->rl_cfg3, CSR_READ_1(sc, sc->rl_cfg3) |
		    RL_CFG3_JUMBO_EN0);
		switch (sc->rl_hwrev->rl_rev) {
		case RL_HWREV_8168DP:
			break;
		case RL_HWREV_8168E:
			CSR_WRITE_1(sc, sc->rl_cfg4,
			    CSR_READ_1(sc, sc->rl_cfg4) | 0x01);
			break;
		default:
			CSR_WRITE_1(sc, sc->rl_cfg4,
			    CSR_READ_1(sc, sc->rl_cfg4) | RL_CFG4_JUMBO_EN1);
		}
	} else {
		CSR_WRITE_1(sc, sc->rl_cfg3, CSR_READ_1(sc, sc->rl_cfg3) &
		    ~RL_CFG3_JUMBO_EN0);
		switch (sc->rl_hwrev->rl_rev) {
		case RL_HWREV_8168DP:
			break;
		case RL_HWREV_8168E:
			CSR_WRITE_1(sc, sc->rl_cfg4,
			    CSR_READ_1(sc, sc->rl_cfg4) & ~0x01);
			break;
		default:
			CSR_WRITE_1(sc, sc->rl_cfg4,
			    CSR_READ_1(sc, sc->rl_cfg4) & ~RL_CFG4_JUMBO_EN1);
		}
	}
	CSR_WRITE_1(sc, RL_EECMD, RL_EEMODE_OFF);

	switch (sc->rl_hwrev->rl_rev) {
	case RL_HWREV_8168DP:
		pci_set_max_read_req(sc->rl_dev, 4096);
		break;
	default:
		if (jumbo != 0)
			pci_set_max_read_req(sc->rl_dev, 512);
		else
			pci_set_max_read_req(sc->rl_dev, 4096);
	}
}