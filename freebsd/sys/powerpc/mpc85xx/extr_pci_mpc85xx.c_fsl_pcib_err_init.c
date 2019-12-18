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
typedef  void* uint16_t ;
struct fsl_pcib_softc {scalar_t__ sc_pcie_capreg; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; scalar_t__ sc_pcie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_CTL_FER_ENABLE ; 
 int PCIEM_CTL_NFER_ENABLE ; 
 int PCIEM_CTL_URR_ENABLE ; 
 scalar_t__ PCIER_DEVICE_CTL ; 
 scalar_t__ PCIER_DEVICE_STA ; 
 scalar_t__ PCIR_SECSTAT_1 ; 
 int /*<<< orphan*/  REG_PEX_ERR_DR ; 
 int /*<<< orphan*/  REG_PEX_ERR_EN ; 
 int /*<<< orphan*/  REG_PEX_MES_DR ; 
 int /*<<< orphan*/  REG_PEX_MES_IER ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fsl_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 void* fsl_pcib_cfgread (struct fsl_pcib_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  fsl_pcib_cfgwrite (struct fsl_pcib_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
fsl_pcib_err_init(device_t dev)
{
	struct fsl_pcib_softc *sc;
	uint16_t sec_stat, dsr;
	uint32_t dcr, err_en;

	sc = device_get_softc(dev);

	sec_stat = fsl_pcib_cfgread(sc, 0, 0, 0, PCIR_SECSTAT_1, 2);
	if (sec_stat)
		fsl_pcib_cfgwrite(sc, 0, 0, 0, PCIR_SECSTAT_1, 0xffff, 2);
	if (sc->sc_pcie) {
		/* Clear error bits */
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_PEX_MES_IER,
		    0xffffffff);
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_PEX_MES_DR,
		    0xffffffff);
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_PEX_ERR_DR,
		    0xffffffff);

		dsr = fsl_pcib_cfgread(sc, 0, 0, 0,
		    sc->sc_pcie_capreg + PCIER_DEVICE_STA, 2);
		if (dsr)
			fsl_pcib_cfgwrite(sc, 0, 0, 0,
			    sc->sc_pcie_capreg + PCIER_DEVICE_STA,
			    0xffff, 2);

		/* Enable all errors reporting */
		err_en = 0x00bfff00;
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_PEX_ERR_EN,
		    err_en);

		/* Enable error reporting: URR, FER, NFER */
		dcr = fsl_pcib_cfgread(sc, 0, 0, 0,
		    sc->sc_pcie_capreg + PCIER_DEVICE_CTL, 4);
		dcr |= PCIEM_CTL_URR_ENABLE | PCIEM_CTL_FER_ENABLE |
		    PCIEM_CTL_NFER_ENABLE;
		fsl_pcib_cfgwrite(sc, 0, 0, 0,
		    sc->sc_pcie_capreg + PCIER_DEVICE_CTL, dcr, 4);
	}
}