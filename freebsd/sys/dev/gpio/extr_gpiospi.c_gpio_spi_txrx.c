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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct gpio_spi_softc {int sc_miso; int /*<<< orphan*/  sc_sclk; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sc_mosi; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  GPIOBUS_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SPIBUS_MODE_CPHA ; 
 int SPIBUS_MODE_CPOL ; 
 int /*<<< orphan*/  gpio_delay (struct gpio_spi_softc*) ; 

__attribute__((used)) static uint8_t
gpio_spi_txrx(struct gpio_spi_softc *sc, int cs, int mode, uint8_t data)
{
	uint32_t mask, out = 0;
	unsigned int bit;


	/* called with locked gpiobus */

	for (mask = 0x80; mask > 0; mask >>= 1) {
		if ((mode == SPIBUS_MODE_CPOL) ||
		    (mode == SPIBUS_MODE_CPHA)) {
			/* If mode 1 or 2 */

			/* first step */
			GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
			    sc->sc_mosi, (data & mask)?1:0);
			GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
			    sc->sc_sclk, 0);
			gpio_delay(sc);
			/* second step */
			if (sc->sc_miso != 0xff) {
				GPIOBUS_PIN_GET(sc->sc_busdev, sc->sc_dev,
				    sc->sc_miso, &bit);
				out |= bit?mask:0;
			}
			/* Data captured */
			gpio_delay(sc);
			GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
			    sc->sc_sclk, 1);
			gpio_delay(sc);
		} else {
			/* If mode 0 or 3 */

			/* first step */
			GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
			    sc->sc_mosi, (data & mask)?1:0);
			GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
			    sc->sc_sclk, 1);
			gpio_delay(sc);
			/* second step */
			if (sc->sc_miso != 0xff) {
				GPIOBUS_PIN_GET(sc->sc_busdev, sc->sc_dev,
				    sc->sc_miso, &bit);
				out |= bit?mask:0;
			}
			 /* Data captured */
			gpio_delay(sc);
			GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
			    sc->sc_sclk, 0);
			gpio_delay(sc);
		}
	}

	return (out & 0xff);
}