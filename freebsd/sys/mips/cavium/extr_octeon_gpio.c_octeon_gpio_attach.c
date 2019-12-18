#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_gpio_softc {int gpio_npins; int /*<<< orphan*/ * busdev; TYPE_3__* gpio_pins; int /*<<< orphan*/  dev; int /*<<< orphan*/ * gpio_ih; struct octeon_gpio_softc** gpio_intr_cookies; int /*<<< orphan*/ ** gpio_irq_res; int /*<<< orphan*/ * gpio_irq_rid; int /*<<< orphan*/  gpio_mtx; } ;
struct octeon_gpio_pin {int /*<<< orphan*/  flags; int /*<<< orphan*/  pin; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int int_en; scalar_t__ int_type; int /*<<< orphan*/  rx_xor; int /*<<< orphan*/  tx_oe; } ;
struct TYPE_5__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_2__ cvmx_gpio_bit_cfgx_t ;
struct TYPE_6__ {scalar_t__ gp_flags; int /*<<< orphan*/  gp_caps; int /*<<< orphan*/  gp_pin; int /*<<< orphan*/  gp_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GPIO_BIT_CFGX (int) ; 
 int /*<<< orphan*/  DEFAULT_CAPS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int OCTEON_GPIO_IRQS ; 
 scalar_t__ OCTEON_GPIO_IRQ_EDGE ; 
 scalar_t__ OCTEON_IRQ_GPIO0 ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct octeon_gpio_softc**,int /*<<< orphan*/ *) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct octeon_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_gpio_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_gpio_filter ; 
 int /*<<< orphan*/  octeon_gpio_intr ; 
 int /*<<< orphan*/  octeon_gpio_pin_configure (struct octeon_gpio_softc*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct octeon_gpio_pin* octeon_gpio_pins ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
octeon_gpio_attach(device_t dev)
{
	struct octeon_gpio_softc *sc = device_get_softc(dev);
	struct octeon_gpio_pin *pinp;
	cvmx_gpio_bit_cfgx_t gpio_cfgx;
	
	int i;

	KASSERT((device_get_unit(dev) == 0),
	    ("octeon_gpio: Only one gpio module supported"));

	mtx_init(&sc->gpio_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	for ( i = 0; i < OCTEON_GPIO_IRQS; i++) {
		if ((sc->gpio_irq_res[i] = bus_alloc_resource(dev, 
		    SYS_RES_IRQ, &sc->gpio_irq_rid[i], 
		    OCTEON_IRQ_GPIO0 + i, OCTEON_IRQ_GPIO0 + i, 1, 
		    RF_SHAREABLE | RF_ACTIVE)) == NULL) {
			device_printf(dev, "unable to allocate IRQ resource\n");
			octeon_gpio_detach(dev);
			return (ENXIO);
		}

		sc->gpio_intr_cookies[i] = sc;
		if ((bus_setup_intr(dev, sc->gpio_irq_res[i], INTR_TYPE_MISC, 
	    	    octeon_gpio_filter, octeon_gpio_intr, 
		    &(sc->gpio_intr_cookies[i]), &sc->gpio_ih[i]))) {
			device_printf(dev,
		    	"WARNING: unable to register interrupt handler\n");
			octeon_gpio_detach(dev);
			return (ENXIO);
		}
	}

	sc->dev = dev;
	/* Configure all pins as input */
	/* disable interrupts for all pins */
	pinp = octeon_gpio_pins;
	i = 0;
	while (pinp->name) {
		strncpy(sc->gpio_pins[i].gp_name, pinp->name, GPIOMAXNAME);
		sc->gpio_pins[i].gp_pin = pinp->pin;
		sc->gpio_pins[i].gp_caps = DEFAULT_CAPS;
		sc->gpio_pins[i].gp_flags = 0;
		octeon_gpio_pin_configure(sc, &sc->gpio_pins[i], pinp->flags);
		pinp++;
		i++;
	}

	sc->gpio_npins = i;

#if 0
	/*
	 * Sample: how to enable edge-triggered interrupt
	 * for GPIO pin
	 */
	gpio_cfgx.u64 = cvmx_read_csr(CVMX_GPIO_BIT_CFGX(7));
	gpio_cfgx.s.int_en = 1;
	gpio_cfgx.s.int_type = OCTEON_GPIO_IRQ_EDGE;
	cvmx_write_csr(CVMX_GPIO_BIT_CFGX(7), gpio_cfgx.u64);
#endif

	if (bootverbose) {
		for (i = 0; i < 16; i++) {
			gpio_cfgx.u64 = cvmx_read_csr(CVMX_GPIO_BIT_CFGX(i));
			device_printf(dev, "[pin%d] output=%d, invinput=%d, intr=%d, intr_type=%s\n", 
			    i, gpio_cfgx.s.tx_oe, gpio_cfgx.s.rx_xor, 
			    gpio_cfgx.s.int_en, gpio_cfgx.s.int_type ? "rising edge" : "level");
		}
	}
	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL) {
		octeon_gpio_detach(dev);
		return (ENXIO);
	}

	return (0);
}