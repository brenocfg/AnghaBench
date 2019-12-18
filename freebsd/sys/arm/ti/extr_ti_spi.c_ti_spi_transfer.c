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
struct ti_spi_softc {int sc_numcs; int sc_flags; int sc_cs; scalar_t__ sc_len; int sc_fifolvl; scalar_t__ sc_written; scalar_t__ sc_read; struct spi_command* sc_cmd; int /*<<< orphan*/  sc_mtx; } ;
struct spi_command {scalar_t__ tx_cmd_sz; scalar_t__ rx_cmd_sz; scalar_t__ tx_data_sz; scalar_t__ rx_data_sz; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MCSPI_CONF_CH (int) ; 
 int MCSPI_CONF_DMAR ; 
 int MCSPI_CONF_DMAW ; 
 int MCSPI_CONF_DPE0 ; 
 int MCSPI_CONF_DPE1 ; 
 int MCSPI_CONF_EPOL ; 
 int MCSPI_CONF_FFER ; 
 int MCSPI_CONF_FFEW ; 
 int MCSPI_CONF_FORCE ; 
 int MCSPI_CONF_IS ; 
 int MCSPI_CONF_SBE ; 
 int MCSPI_CONF_SBPOL ; 
 int MCSPI_CONF_TURBO ; 
 int MCSPI_CONF_WL8BITS ; 
 int /*<<< orphan*/  MCSPI_CTRL_CH (int) ; 
 int MCSPI_CTRL_ENABLE ; 
 int /*<<< orphan*/  MCSPI_IRQENABLE ; 
 int /*<<< orphan*/  MCSPI_IRQSTATUS ; 
 int /*<<< orphan*/  MCSPI_XFERLEVEL ; 
 int SPIBUS_CS_HIGH ; 
 int TI_SPI_BUSY ; 
 int /*<<< orphan*/  TI_SPI_FIFOSZ ; 
 int /*<<< orphan*/  TI_SPI_LOCK (struct ti_spi_softc*) ; 
 int TI_SPI_READ (struct ti_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_SPI_UNLOCK (struct ti_spi_softc*) ; 
 int /*<<< orphan*/  TI_SPI_WRITE (struct ti_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ti_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spibus_get_clock (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spibus_get_mode (int /*<<< orphan*/ ,int*) ; 
 int ti_spi_gcd (scalar_t__,int /*<<< orphan*/ ) ; 
 int ti_spi_pio_transfer (struct ti_spi_softc*) ; 
 int /*<<< orphan*/  ti_spi_set_clock (struct ti_spi_softc*,int,int) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	int err;
	struct ti_spi_softc *sc;
	uint32_t clockhz, cs, mode, reg;

	sc = device_get_softc(dev);

	KASSERT(cmd->tx_cmd_sz == cmd->rx_cmd_sz, 
	    ("TX/RX command sizes should be equal"));
	KASSERT(cmd->tx_data_sz == cmd->rx_data_sz, 
	    ("TX/RX data sizes should be equal"));

	/* Get the proper chip select for this child. */
	spibus_get_cs(child, &cs);
	spibus_get_clock(child, &clockhz);
	spibus_get_mode(child, &mode);

	cs &= ~SPIBUS_CS_HIGH;

	if (cs > sc->sc_numcs) {
		device_printf(dev, "Invalid chip select %d requested by %s\n",
		    cs, device_get_nameunit(child));
		return (EINVAL);
	}

	if (mode > 3)
	{
	    device_printf(dev, "Invalid mode %d requested by %s\n", mode,
		    device_get_nameunit(child));
	    return (EINVAL);
	}

	TI_SPI_LOCK(sc);

	/* If the controller is in use wait until it is available. */
	while (sc->sc_flags & TI_SPI_BUSY)
		mtx_sleep(dev, &sc->sc_mtx, 0, "ti_spi", 0);

	/* Now we have control over SPI controller. */
	sc->sc_flags = TI_SPI_BUSY;

	/* Save the SPI command data. */
	sc->sc_cs = cs;
	sc->sc_cmd = cmd;
	sc->sc_read = 0;
	sc->sc_written = 0;
	sc->sc_len = cmd->tx_cmd_sz + cmd->tx_data_sz;
	sc->sc_fifolvl = ti_spi_gcd(sc->sc_len, TI_SPI_FIFOSZ);
	if (sc->sc_fifolvl < 2 || sc->sc_len > 0xffff)
		sc->sc_fifolvl = 1;	/* FIFO disabled. */
	/* Disable FIFO for now. */
	sc->sc_fifolvl = 1;

	/* Set the bus frequency. */
	ti_spi_set_clock(sc, sc->sc_cs, clockhz);

	/* Disable the FIFO. */
	TI_SPI_WRITE(sc, MCSPI_XFERLEVEL, 0);

	/* 8 bits word, d0 miso, d1 mosi, mode 0 and CS active low. */
	reg = TI_SPI_READ(sc, MCSPI_CONF_CH(sc->sc_cs));
	reg &= ~(MCSPI_CONF_FFER | MCSPI_CONF_FFEW | MCSPI_CONF_SBPOL |
	    MCSPI_CONF_SBE | MCSPI_CONF_TURBO | MCSPI_CONF_IS |
	    MCSPI_CONF_DPE1 | MCSPI_CONF_DPE0 | MCSPI_CONF_DMAR |
	    MCSPI_CONF_DMAW | MCSPI_CONF_EPOL);
	reg |= MCSPI_CONF_DPE0 | MCSPI_CONF_EPOL | MCSPI_CONF_WL8BITS;
	reg |= mode; /* POL and PHA are the low bits, we can just OR-in mode */
	TI_SPI_WRITE(sc, MCSPI_CONF_CH(sc->sc_cs), reg);

#if 0
	/* Enable channel interrupts. */
	reg = TI_SPI_READ(sc, MCSPI_IRQENABLE);
	reg |= 0xf;
	TI_SPI_WRITE(sc, MCSPI_IRQENABLE, reg);
#endif

	/* Start the transfer. */
	reg = TI_SPI_READ(sc, MCSPI_CTRL_CH(sc->sc_cs));
	TI_SPI_WRITE(sc, MCSPI_CTRL_CH(sc->sc_cs), reg | MCSPI_CTRL_ENABLE);

	/* Force CS on. */
	reg = TI_SPI_READ(sc, MCSPI_CONF_CH(sc->sc_cs));
	TI_SPI_WRITE(sc, MCSPI_CONF_CH(sc->sc_cs), reg |= MCSPI_CONF_FORCE);

	err = 0;
	if (sc->sc_fifolvl == 1)
		err = ti_spi_pio_transfer(sc);

	/* Force CS off. */
	reg = TI_SPI_READ(sc, MCSPI_CONF_CH(sc->sc_cs));
	reg &= ~MCSPI_CONF_FORCE;
	TI_SPI_WRITE(sc, MCSPI_CONF_CH(sc->sc_cs), reg);

	/* Disable IRQs. */
	reg = TI_SPI_READ(sc, MCSPI_IRQENABLE);
	reg &= ~0xf;
	TI_SPI_WRITE(sc, MCSPI_IRQENABLE, reg);
	TI_SPI_WRITE(sc, MCSPI_IRQSTATUS, 0xf);

	/* Disable the SPI channel. */
	reg = TI_SPI_READ(sc, MCSPI_CTRL_CH(sc->sc_cs));
	reg &= ~MCSPI_CTRL_ENABLE;
	TI_SPI_WRITE(sc, MCSPI_CTRL_CH(sc->sc_cs), reg);

	/* Disable FIFO. */
	reg = TI_SPI_READ(sc, MCSPI_CONF_CH(sc->sc_cs));
	reg &= ~(MCSPI_CONF_FFER | MCSPI_CONF_FFEW);
	TI_SPI_WRITE(sc, MCSPI_CONF_CH(sc->sc_cs), reg);

	/* Release the controller and wakeup the next thread waiting for it. */
	sc->sc_flags = 0;
	wakeup_one(dev);
	TI_SPI_UNLOCK(sc);

	return (err);
}