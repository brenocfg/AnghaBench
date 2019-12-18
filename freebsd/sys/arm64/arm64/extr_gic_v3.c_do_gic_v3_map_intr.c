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
typedef  scalar_t__ u_int ;
struct intr_map_data_msi {int dummy; } ;
struct intr_map_data_fdt {int /*<<< orphan*/  cells; int /*<<< orphan*/  ncells; } ;
struct intr_map_data_acpi {scalar_t__ irq; int pol; int trig; } ;
struct intr_map_data {int type; } ;
struct gic_v3_softc {scalar_t__ gic_nirqs; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  INTR_MAP_DATA_ACPI 136 
#define  INTR_MAP_DATA_FDT 135 
#define  INTR_MAP_DATA_MSI 134 
#define  INTR_POLARITY_CONFORM 133 
#define  INTR_POLARITY_HIGH 132 
#define  INTR_POLARITY_LOW 131 
#define  INTR_TRIGGER_CONFORM 130 
#define  INTR_TRIGGER_EDGE 129 
#define  INTR_TRIGGER_LEVEL 128 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_map_fdt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  gic_map_msi (int /*<<< orphan*/ ,struct intr_map_data_msi*,scalar_t__*,int*,int*) ; 

__attribute__((used)) static int
do_gic_v3_map_intr(device_t dev, struct intr_map_data *data, u_int *irqp,
    enum intr_polarity *polp, enum intr_trigger *trigp)
{
	struct gic_v3_softc *sc;
	enum intr_polarity pol;
	enum intr_trigger trig;
	struct intr_map_data_msi *dam;
#ifdef FDT
	struct intr_map_data_fdt *daf;
#endif
#ifdef DEV_ACPI
	struct intr_map_data_acpi *daa;
#endif
	u_int irq;

	sc = device_get_softc(dev);

	switch (data->type) {
#ifdef FDT
	case INTR_MAP_DATA_FDT:
		daf = (struct intr_map_data_fdt *)data;
		if (gic_map_fdt(dev, daf->ncells, daf->cells, &irq, &pol,
		    &trig) != 0)
			return (EINVAL);
		break;
#endif
#ifdef DEV_ACPI
	case INTR_MAP_DATA_ACPI:
		daa = (struct intr_map_data_acpi *)data;
		irq = daa->irq;
		pol = daa->pol;
		trig = daa->trig;
		break;
#endif
	case INTR_MAP_DATA_MSI:
		/* SPI-mapped MSI */
		dam = (struct intr_map_data_msi *)data;
		if (gic_map_msi(dev, dam, &irq, &pol, &trig) != 0)
			return (EINVAL);
		break;
	default:
		return (EINVAL);
	}

	if (irq >= sc->gic_nirqs)
		return (EINVAL);
	switch (pol) {
	case INTR_POLARITY_CONFORM:
	case INTR_POLARITY_LOW:
	case INTR_POLARITY_HIGH:
		break;
	default:
		return (EINVAL);
	}
	switch (trig) {
	case INTR_TRIGGER_CONFORM:
	case INTR_TRIGGER_EDGE:
	case INTR_TRIGGER_LEVEL:
		break;
	default:
		return (EINVAL);
	}

	*irqp = irq;
	if (polp != NULL)
		*polp = pol;
	if (trigp != NULL)
		*trigp = trig;
	return (0);
}