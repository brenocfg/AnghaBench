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
typedef  int u_long ;
struct spi_command {scalar_t__ tx_cmd_sz; scalar_t__ rx_cmd_sz; scalar_t__ tx_data_sz; scalar_t__ rx_data_sz; } ;
struct fsl_espi_softc {int sc_num_cs; int sc_flags; scalar_t__ sc_len; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_written; scalar_t__ sc_read; struct spi_command* sc_cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ESPI_CSMODE (int) ; 
 int ESPI_CSMODE_CI ; 
 int ESPI_CSMODE_CP ; 
 int ESPI_CSMODE_CSCG (int) ; 
 int ESPI_CSMODE_DIV16 ; 
 int ESPI_CSMODE_LEN (int) ; 
 int ESPI_CSMODE_PM_S ; 
 int ESPI_CSMODE_POL ; 
 int ESPI_CSMODE_REV ; 
 int /*<<< orphan*/  ESPI_SPCOM ; 
 int ESPI_SPCOM_CS_S ; 
 scalar_t__ ESPI_SPCOM_TRANLEN_M ; 
 int ESPI_SPIE_DON ; 
 int ESPI_SPIE_RXF ; 
 int ESPI_SPIE_TXE ; 
 int /*<<< orphan*/  ESPI_SPIM ; 
 int EWOULDBLOCK ; 
 int FSL_ESPI_BUSY ; 
 int /*<<< orphan*/  FSL_ESPI_LOCK (struct fsl_espi_softc*) ; 
 int /*<<< orphan*/  FSL_ESPI_UNLOCK (struct fsl_espi_softc*) ; 
 int /*<<< orphan*/  FSL_ESPI_WRITE (struct fsl_espi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SPIBUS_CS_HIGH ; 
 int SPIBUS_MODE_CPHA ; 
 int SPIBUS_MODE_CPOL ; 
 int SPIBUS_MODE_CPOL_CPHA ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct fsl_espi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int howmany (int,int) ; 
 int hz ; 
 int max (int,int) ; 
 int mpc85xx_get_system_clock () ; 
 int mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spibus_get_clock (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spibus_get_mode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fsl_espi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct fsl_espi_softc *sc;
	u_long plat_clk;
	uint32_t csmode, spi_clk, spi_mode;
	int cs, err, pm;

	sc = device_get_softc(dev);

	KASSERT(cmd->tx_cmd_sz == cmd->rx_cmd_sz, 
	    ("TX/RX command sizes should be equal"));
	KASSERT(cmd->tx_data_sz == cmd->rx_data_sz, 
	    ("TX/RX data sizes should be equal"));

	/* Restrict transmit length to command max length */
	if (cmd->tx_cmd_sz + cmd->tx_data_sz > ESPI_SPCOM_TRANLEN_M + 1) {
		return (EINVAL);
	}

	/* Get the proper chip select for this child. */
	spibus_get_cs(child, &cs);
	if (cs < 0 || cs > sc->sc_num_cs) {
		device_printf(dev,
		    "Invalid chip select %d requested by %s\n", cs,
		    device_get_nameunit(child));
		return (EINVAL);
	}
	spibus_get_clock(child, &spi_clk);
	spibus_get_mode(child, &spi_mode);

	FSL_ESPI_LOCK(sc);

	/* If the controller is in use wait until it is available. */
	while (sc->sc_flags & FSL_ESPI_BUSY)
		mtx_sleep(dev, &sc->sc_mtx, 0, "fsl_espi", 0);

	/* Now we have control over SPI controller. */
	sc->sc_flags = FSL_ESPI_BUSY;

	/* Save a pointer to the SPI command. */
	sc->sc_cmd = cmd;
	sc->sc_read = 0;
	sc->sc_written = 0;
	sc->sc_len = cmd->tx_cmd_sz + cmd->tx_data_sz;

	plat_clk = mpc85xx_get_system_clock();
	spi_clk = max(spi_clk, plat_clk / (16 * 16));
	if (plat_clk == 0) {
		device_printf(dev,
		    "unable to get platform clock, giving up.\n");
		return (EINVAL);
	}
	csmode = 0;
	if (plat_clk > spi_clk * 16 * 2) {
		csmode |= ESPI_CSMODE_DIV16;
		plat_clk /= 16;
	}
	pm = howmany(plat_clk, spi_clk * 2) - 1;
	if (pm < 0)
		pm = 1;
	if (pm > 15)
		pm = 15;

	csmode |= (pm << ESPI_CSMODE_PM_S);
	csmode |= ESPI_CSMODE_REV;
	if (spi_mode == SPIBUS_MODE_CPOL || spi_mode == SPIBUS_MODE_CPOL_CPHA)
		csmode |= ESPI_CSMODE_CI;
	if (spi_mode == SPIBUS_MODE_CPHA || spi_mode == SPIBUS_MODE_CPOL_CPHA)
		csmode |= ESPI_CSMODE_CP;
	if (!(cs & SPIBUS_CS_HIGH))
		csmode |= ESPI_CSMODE_POL;
	csmode |= ESPI_CSMODE_LEN(7);/* Only deal with 8-bit characters. */
	csmode |= ESPI_CSMODE_CSCG(1); /* XXX: Make this configurable? */
	/* Configure transaction */
	FSL_ESPI_WRITE(sc, ESPI_SPCOM, (cs << ESPI_SPCOM_CS_S) | (sc->sc_len - 1));
	FSL_ESPI_WRITE(sc, ESPI_CSMODE(cs), csmode);
	/* Enable interrupts we need. */
	FSL_ESPI_WRITE(sc, ESPI_SPIM,
	    ESPI_SPIE_TXE | ESPI_SPIE_DON | ESPI_SPIE_RXF);

	/* Wait for the transaction to complete. */
	err = mtx_sleep(dev, &sc->sc_mtx, 0, "fsl_espi", hz * 2);
	FSL_ESPI_WRITE(sc, ESPI_SPIM, 0);

	/* Release the controller and wakeup the next thread waiting for it. */
	sc->sc_flags = 0;
	wakeup_one(dev);
	FSL_ESPI_UNLOCK(sc);

	/*
	 * Check for transfer timeout.  The SPI controller doesn't
	 * return errors.
	 */
	if (err == EWOULDBLOCK) {
		device_printf(sc->sc_dev, "SPI error\n");
		err = EIO;
	}

	return (err);
}