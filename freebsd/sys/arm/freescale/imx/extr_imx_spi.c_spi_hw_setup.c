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
typedef  unsigned int uint32_t ;
typedef  int u_int ;
struct spi_softc {int ctlreg; } ;

/* Variables and functions */
 unsigned int CFGREG_SCLKCTL_SHIFT ; 
 unsigned int CFGREG_SCLKPHA_SHIFT ; 
 unsigned int CFGREG_SCLKPOL_SHIFT ; 
 unsigned int CFGREG_SSPOL_SHIFT ; 
 int CTLREG_BLEN_SHIFT ; 
 int CTLREG_CMODES_MASTER ; 
 int CTLREG_EN ; 
 int CTLREG_SMC ; 
 unsigned int DMA_RX_THRESH_SHIFT ; 
 unsigned int DMA_TX_THRESH_SHIFT ; 
 int /*<<< orphan*/  ECSPI_CFGREG ; 
 int /*<<< orphan*/  ECSPI_CTLREG ; 
 int /*<<< orphan*/  ECSPI_DMAREG ; 
 unsigned int FIFO_RXTHRESH ; 
 unsigned int FIFO_TXTHRESH ; 
 int /*<<< orphan*/  RD4 (struct spi_softc*,int /*<<< orphan*/ ) ; 
 int SPIBUS_CS_HIGH ; 
 int SPIBUS_MODE_CPHA ; 
 int SPIBUS_MODE_CPOL ; 
 int /*<<< orphan*/  WR4 (struct spi_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int spi_calc_clockdiv (struct spi_softc*,int) ; 

__attribute__((used)) static void
spi_hw_setup(struct spi_softc *sc, u_int cs, u_int mode, u_int freq)
{
	uint32_t reg;

	/*
	 * Set up control register, and write it first to bring the device out
	 * of reset.
	 */
	sc->ctlreg  = CTLREG_EN | CTLREG_CMODES_MASTER | CTLREG_SMC;
	sc->ctlreg |= spi_calc_clockdiv(sc, freq);
	sc->ctlreg |= 7 << CTLREG_BLEN_SHIFT; /* XXX byte at a time */
	WR4(sc, ECSPI_CTLREG, sc->ctlreg);

	/*
	 * Set up the config register.  Note that we do all transfers with the
	 * SPI hardware's chip-select set to zero.  The actual chip select is
	 * handled with a gpio pin.
	 */
	reg = 0;
	if (cs & SPIBUS_CS_HIGH)
		reg |= 1u << CFGREG_SSPOL_SHIFT;
	if (mode & SPIBUS_MODE_CPHA)
		reg |= 1u << CFGREG_SCLKPHA_SHIFT;
	if (mode & SPIBUS_MODE_CPOL) {
		reg |= 1u << CFGREG_SCLKPOL_SHIFT;
		reg |= 1u << CFGREG_SCLKCTL_SHIFT;
	}
	WR4(sc, ECSPI_CFGREG, reg);

	/*
	 * Set up the rx/tx FIFO interrupt thresholds.
	 */
	reg  = (FIFO_RXTHRESH << DMA_RX_THRESH_SHIFT);
	reg |= (FIFO_TXTHRESH << DMA_TX_THRESH_SHIFT);
	WR4(sc, ECSPI_DMAREG, reg);

	/*
	 * Do a dummy read, to make sure the preceding writes reach the spi
	 * hardware before we assert any gpio chip select.
	 */
	(void)RD4(sc, ECSPI_CFGREG);
}