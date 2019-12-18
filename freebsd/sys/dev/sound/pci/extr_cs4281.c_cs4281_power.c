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
struct sc_info {int power; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_CWPR ; 
 int /*<<< orphan*/  CS4281PCI_CWPR_MAGIC ; 
 int /*<<< orphan*/  CS4281PCI_EPPMC ; 
 int /*<<< orphan*/  CS4281PCI_EPPMC_FPDN ; 
 int /*<<< orphan*/  CS4281PCI_SPMC ; 
 int /*<<< orphan*/  CS4281PCI_SPMC_RSTN ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_clr4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_set4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int
cs4281_power(struct sc_info *sc, int state)
{

    switch (state) {
    case 0:
        /* Permit r/w access to all BA0 registers */
        cs4281_wr(sc, CS4281PCI_CWPR, CS4281PCI_CWPR_MAGIC);
        /* Power on */
        cs4281_clr4(sc, CS4281PCI_EPPMC, CS4281PCI_EPPMC_FPDN);
        break;
    case 3:
    	/* Power off card and codec */
    	cs4281_set4(sc, CS4281PCI_EPPMC, CS4281PCI_EPPMC_FPDN);
    	cs4281_clr4(sc, CS4281PCI_SPMC, CS4281PCI_SPMC_RSTN);
        break;
    }

    DEB(printf("cs4281_power %d -> %d\n", sc->power, state));
    sc->power = state;

    return 0;
}