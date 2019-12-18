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
typedef  int u_int ;
typedef  int pcell_t ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
#define  FDT_INTR_EDGE_FALLING 131 
#define  FDT_INTR_EDGE_RISING 130 
#define  FDT_INTR_LEVEL_HIGH 129 
#define  FDT_INTR_LEVEL_LOW 128 
 int INTR_POLARITY_HIGH ; 
 int INTR_POLARITY_LOW ; 
 int INTR_TRIGGER_EDGE ; 
 int INTR_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
aw_nmi_map_fdt(device_t dev, u_int ncells, pcell_t *cells, u_int *irqp,
    enum intr_polarity *polp, enum intr_trigger *trigp)
{
	u_int irq, tripol;
	enum intr_polarity pol;
	enum intr_trigger trig;

	if (ncells != 2) {
		device_printf(dev, "Invalid #interrupt-cells\n");
		return (EINVAL);
	}

	irq = cells[0];
	if (irq != 0) {
		device_printf(dev, "Controller only support irq 0\n");
		return (EINVAL);
	}

	tripol = cells[1];

	switch (tripol) {
	case FDT_INTR_EDGE_RISING:
		trig = INTR_TRIGGER_EDGE;
		pol  = INTR_POLARITY_HIGH;
		break;
	case FDT_INTR_EDGE_FALLING:
		trig = INTR_TRIGGER_EDGE;
		pol  = INTR_POLARITY_LOW;
		break;
	case FDT_INTR_LEVEL_HIGH:
		trig = INTR_TRIGGER_LEVEL;
		pol  = INTR_POLARITY_HIGH;
		break;
	case FDT_INTR_LEVEL_LOW:
		trig = INTR_TRIGGER_LEVEL;
		pol  = INTR_POLARITY_LOW;
		break;
	default:
		device_printf(dev, "unsupported trigger/polarity 0x%2x\n",
		    tripol);
		return (ENOTSUP);
	}

	*irqp = irq;
	if (polp != NULL)
		*polp = pol;
	if (trigp != NULL)
		*trigp = trig;
	return (0);
}