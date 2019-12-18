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
typedef  int uint32_t ;
struct tegra_pcib_softc {int /*<<< orphan*/  afi_mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_INTR_CODE ; 
 int AFI_INTR_CODE_INT_CODE_SM_MSG ; 
 int AFI_INTR_CODE_MASK ; 
 int /*<<< orphan*/  AFI_INTR_SIGNATURE ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int tegra_pci_intr(void *arg)
{
	struct tegra_pcib_softc *sc = arg;
	uint32_t code, signature;

	code = bus_read_4(sc->afi_mem_res, AFI_INTR_CODE) & AFI_INTR_CODE_MASK;
	signature = bus_read_4(sc->afi_mem_res, AFI_INTR_SIGNATURE);
	bus_write_4(sc->afi_mem_res, AFI_INTR_CODE, 0);
	if (code == AFI_INTR_CODE_INT_CODE_SM_MSG)
		return(FILTER_STRAY);

	printf("tegra_pci_intr: code %x sig %x\n", code, signature);
	return (FILTER_HANDLED);
}